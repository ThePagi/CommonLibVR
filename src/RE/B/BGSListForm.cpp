#include "RE/B/BGSListForm.h"

namespace RE
{
	void BGSListForm::AddForm(TESForm* a_form)
	{
		using func_t = decltype(&BGSListForm::AddForm);
		REL::Relocation<func_t> func{ Offset::BGSListForm::AddForm };
		return func(this, a_form);
	}

	bool BGSListForm::HasForm(const TESForm* a_form) const
	{
		if (!a_form) {
			return false;
		}

		auto ptrIt = std::find(forms.begin(), forms.end(), a_form);
		if (ptrIt != forms.end()) {
			return true;
		}

		if (!scriptAddedTempForms) {
			return false;
		}

		auto idIt = std::find(scriptAddedTempForms->begin(), scriptAddedTempForms->end(), a_form->formID);
		return idIt != scriptAddedTempForms->end();
	}

	bool BGSListForm::HasForm(FormID a_formID) const
	{
		auto form = TESForm::LookupByID(a_formID);
		return HasForm(form);
	}

	void BGSListForm::ForEachForm(std::function<bool(TESForm&)> a_callback) const
	{
		for (const auto& form : forms) {
			if (form && !a_callback(*form)) {
				return;
			}
		}
		if (scriptAddedTempForms) {
			for (const auto& addedFormID : *scriptAddedTempForms) {
				if (const auto addedForm = TESForm::LookupByID(addedFormID); !a_callback(*addedForm)) {
					return;
				}
			}
		}
	}
}
