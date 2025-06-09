#include "GalgameUserWidget.h"
// 步骤：
// 1. 检查 UButton 的 OnClicked 类型。UE4/UE5 的 UButton->OnClicked 是 FOnButtonClickedEvent 类型，只支持 AddDynamic 和 AddUObject，不支持 AddLambda。
// 2. 如果需要传递参数，可以用成员函数绑定，并在类中保存参数。
// 3. 修改 BindButtonOnClickWithParameter，使用 AddDynamic 绑定成员函数。
// 4. 在 UGalgameUserWidget 类中添加一个成员变量保存 Sourece。

void UGalgameUserWidget::BindButtonOnClick(const TArray<UButton*>& Buttons, const TArray<UObject*>& Sources)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Selection."));
	if (Buttons.Num() != Sources.Num())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Buttons and Sources must have the same number of elements."));
		return;
	}
	ButtonToSourceMap.Empty();
	for (int32 i = 0; i < Buttons.Num(); i++)
	{
		UButton* Button = Buttons[i];
		UObject* Source = Sources[i];
		if (!Button || !Source) {
		
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("索引 %d 处的按钮或源对象为空！"), i));
			continue;
		}
		ButtonToSourceMap.Add(Button, Source);
		Button->OnClicked.AddDynamic(this, &UGalgameUserWidget::HandleButtonClicked);
	}
}
void UGalgameUserWidget::HandleButtonClicked()
{
	for (const auto& Elem : ButtonToSourceMap)
	{
		UButton* Button = Elem.Key;
		if (Button && Button->HasKeyboardFocus())
		{
			UObject* Source = Elem.Value;
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Button %s clicked!"), *Button->GetName()));
			SelectionBtn(Source);
			break;
		}
	}
	
}
