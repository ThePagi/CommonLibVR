#pragma once

#include "RE/B/BSLightingShaderProperty.h"
#include "RE/N/NiAVObject.h"
#include "RE/N/NiRTTI.h"
#include "RE/N/NiSkinPartition.h"
#include "RE/N/NiSmartPointer.h"

namespace RE
{
	class BSMultiIndexTriShape;
	class BSSkinnedDecalTriShape;
	class NiProperty;
	class NiSkinInstance;

	class BSGeometry : public NiAVObject
	{
	public:
		inline static constexpr auto RTTI = RTTI_BSGeometry;
		inline static constexpr auto Ni_RTTI = NiRTTI_BSGeometry;

		enum class Type
		{
			kGeometry = 0,
			kParticles = 1,
			kStripParticles = 2,
			kTriShape = 3,
			kDynamicTriShape = 4,
			kMeshLODTriShape = 5,
			kLODMultiIndexTriShape = 6,
			kMultiIndexTriShape = 7,
			kSubIndexTriShape = 8,
			kSubIndexLandTriShape = 9,
			kMultiStreamInstanceTriShape = 10,
			kParticleShaderDynamicTriShape = 11,
			kLines = 12,
			kDynamicLines = 13,
			kInstanceGroup = 14
		};

		struct States
		{
			enum State
			{
				kProperty,
				kEffect,
				kTotal
			};
		};

		~BSGeometry() override;  // 00

		// override (NiAVObject)
		const NiRTTI* GetRTTI() const override;                                                                                    // 02
		BSGeometry*   AsGeometry() override;                                                                                       // 07 - { return this; }
		void          LoadBinary(NiStream& a_stream) override;                                                                     // 18
		void          LinkObject(NiStream& a_stream) override;                                                                     // 19
		bool          RegisterStreamables(NiStream& a_stream) override;                                                            // 1A
		void          SaveBinary(NiStream& a_stream) override;                                                                     // 1B
		bool          IsEqual(NiObject* a_object) override;                                                                        // 1C - { return false; }
		void          ProcessClone(NiCloningProcess& a_cloning) override;                                                          // 1D
		void          PostLinkObject(NiStream& a_stream) override;                                                                 // 1E
		void          AttachProperty(NiAlphaProperty* a_property) override;                                                        // 27
		void          SetSelectiveUpdateFlags(bool& a_selectiveUpdate, bool a_selectiveUpdateTransforms, bool& a_rigid) override;  // 2B
		void          UpdateDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;                                     // 2C
		void          UpdateSelectedDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;                             // 2D
		void          UpdateRigidDownwardPass(NiUpdateData& a_data, std::uint32_t a_arg2) override;                                // 2E
		void          UpdateWorldBound() override;                                                                                 // 2F
		void          OnVisible(NiCullingProcess& a_process) override;                                                             // 34

		// add
		virtual BSMultiIndexTriShape*   AsMultiIndexTriShape();    // 35 - { return 0; }
		virtual BSSkinnedDecalTriShape* AsSkinnedDecalTriShape();  // 36 - { return 0; }
		virtual void                    Unk_37(void);              // 37 - { return 0; }

		inline BSLightingShaderProperty* lightingShaderProp_cast()
		{
			if (auto effect = properties[States::kEffect].get(); effect) {
				if (auto rtti = effect->GetRTTI(); rtti) {
					const std::string rttiStr(rtti->GetName());
					if (rttiStr == "BSLightingShaderProperty") {
						return static_cast<BSLightingShaderProperty*>(effect);
					}
				}
			}
			return nullptr;
		}

// members
#ifndef SKYRIMVR
		// members
		NiBound                              modelBound;                  // 110
		NiPointer<NiProperty>                properties[States::kTotal];  // 120
		NiPointer<NiSkinInstance>            skinInstance;                // 130
		BSGraphics::TriShape*                rendererData;                // 138
		void*                                unk140;                      // 140 - smart ptr
		BSGraphics::VertexDesc               vertexDesc;                  // 148
		stl::enumeration<Type, std::uint8_t> type;                        // 150
		std::uint8_t                         pad151;                      // 151
		std::uint16_t                        pad152;                      // 152
		std::uint32_t                        pad154;                      // 154
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSGeometry) == 0x158);
#else
		NiBound                              modelBound;                  // 138
		NiPoint3                             unk148;                      // 148
		NiPoint3                             unk154;                      // 154
		NiPointer<NiProperty>                properties[States::kTotal];  // 160
		NiPointer<NiSkinInstance>            skinInstance;                // 170
		BSGraphics::TriShape*                rendererData;                // 178
		void*                                unk180;                      // 180
		BSGraphics::VertexDesc               vertexDesc;                  // 188
		stl::enumeration<Type, std::uint8_t> type;                        // 190
		std::uint8_t                         pad191;                      // 191
		std::uint16_t                        pad192;                      // 192
		std::uint32_t                        pad194;                      // 194
	private:
		KEEP_FOR_RE()
	};
	static_assert(sizeof(BSGeometry) == 0x198);
#endif
}
