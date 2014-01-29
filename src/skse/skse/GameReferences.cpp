#include "GameReferences.h"
#include "GameObjects.h"
#include "GameForms.h"
#include "GameExtraData.h"
#include "GameRTTI.h"
#include "NiNodes.h"

const _CreateRefHandleByREFR	CreateRefHandleByREFR = (_CreateRefHandleByREFR)0x0065CC00;
const _LookupREFRByHandle		LookupREFRByHandle = (_LookupREFRByHandle)0x004A9180;
const _LookupREFRByHandle2		LookupREFRByHandle2 = (_LookupREFRByHandle2)0x004951F0;

const UInt32 * g_invalidRefHandle = (UInt32*)0x01310630;

UInt32 TESObjectREFR::CreateRefHandle(void)
{
	if (handleRefObject.GetRefCount() > 0)
	{
		UInt32 refHandle = 0;
		CreateRefHandleByREFR(&refHandle, this);
		return refHandle;
	}
	else
	{
		return *g_invalidRefHandle;
	}
}

TESForm * Actor::GetEquippedObject(bool abLeftHand)
{
	if(!processManager) 
		return NULL;

	if(abLeftHand)
		return processManager->equippedObject[ActorProcessManager::kEquippedHand_Left];
	else
		return processManager->equippedObject[ActorProcessManager::kEquippedHand_Right];

	return NULL;
}

TintMask * PlayerCharacter::GetOverlayTintMask(TintMask * original)
{
	SInt32 curIndex = -1;
	if(!overlayTintMasks)
		return NULL;

	TintMask * foundMask;
	for(UInt32 i = 0; i < tintMasks.count; i++)
	{
		tintMasks.GetNthItem(i, foundMask);
		if(foundMask == original) {
			curIndex = i;
			break;
		}
	}

	overlayTintMasks->GetNthItem(curIndex, foundMask);
	if(foundMask)
		return foundMask;

	return NULL;
}

void Actor::UpdateHairColor()
{
	TESNPC* npc = DYNAMIC_CAST(baseForm, TESForm, TESNPC);
	if(npc && npc->headData) {
		BGSColorForm * hairColor = npc->headData->hairColor; // Non-player actors won't have this
		if(hairColor) {
			NiColorA val;
			val.r = hairColor->color.red / 128.0;
			val.g = hairColor->color.green / 128.0;
			val.b = hairColor->color.blue / 128.0;
			NiColorA * color = &val;

			NiNode * model = GetNiRootNode(0);
			if(model) {
				UpdateModelHair(model, &color);
			}
		}
	}
}

void Actor::UpdateSkinColor()
{
	TESNPC* npc = DYNAMIC_CAST(baseForm, TESForm, TESNPC);
	if(npc) {
		NiColorA val;
		val.r = npc->color.red / 255.0;
		val.g = npc->color.green / 255.0;
		val.b = npc->color.blue / 255.0;
		NiColorA * color = &val;

		NiNode * thirdPerson = GetNiRootNode(0);
		NiNode * firstPerson = GetNiRootNode(1);
		if(thirdPerson) {
			UpdateModelSkin(thirdPerson, &color); // Update for 3rd Person
		}
		if(firstPerson) {
			UpdateModelSkin(firstPerson, &color); // Update for 1st Person
		}
	}
}

bool Actor::HasItemAbility(TESForm* baseForm, BaseExtraList * extraData)
{
	if(baseForm) {
		tList<ActiveEffect> * effects = magicTarget.GetActiveEffects();
		for(UInt32 i = 0; i < effects->Count(); i++) {
			ActiveEffect* effect = effects->GetNthItem(i);
			if(effect->sourceItem == baseForm) { // Check the item
				EnchantmentItem * enchantment = NULL;
				TESEnchantableForm * enchantable = DYNAMIC_CAST(baseForm, TESForm, TESEnchantableForm);
				if(enchantable) { // Check the item for a base enchantment
					enchantment = enchantable->enchantment;
				}
				if(extraData) { // Check the extra data for enchantment
					ExtraEnchantment* extraEnchant = static_cast<ExtraEnchantment*>(extraData->GetByType(kExtraData_Enchantment));
					if(extraEnchant) {
						enchantment = extraEnchant->enchant;
					}
				}

				if(effect->item == enchantment) {
					return true;
				}
			}
		}
	}

	return false;
}

void Actor::UpdateItemAbility(TESForm* form, BaseExtraList * extraData, bool bLeftHand)
{
	if(form) {
		if(baseForm->formType == TESObjectWEAP::kTypeID)
			CALL_MEMBER_FN(this, UpdateWeaponAbility)(form, extraData, bLeftHand);
		else if(baseForm->formType == TESObjectARMO::kTypeID)
			CALL_MEMBER_FN(this, UpdateArmorAbility)(form, extraData);
	}
}
