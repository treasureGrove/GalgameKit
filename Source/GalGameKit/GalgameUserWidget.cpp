#include "GalgameUserWidget.h"
// ���裺
// 1. ��� UButton �� OnClicked ���͡�UE4/UE5 �� UButton->OnClicked �� FOnButtonClickedEvent ���ͣ�ֻ֧�� AddDynamic �� AddUObject����֧�� AddLambda��
// 2. �����Ҫ���ݲ����������ó�Ա�����󶨣��������б��������
// 3. �޸� BindButtonOnClickWithParameter��ʹ�� AddDynamic �󶨳�Ա������
// 4. �� UGalgameUserWidget �������һ����Ա�������� Sourece��

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
		
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("���� %d ���İ�ť��Դ����Ϊ�գ�"), i));
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
