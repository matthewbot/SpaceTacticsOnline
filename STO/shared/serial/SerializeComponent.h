#ifndef STO_SHARED_SERIALIZECOMPONENT_H
#define STO_SHARED_SERIALIZECOMPONENT_H

#include <STO/shared/entity/EntityComponent.h>
#include <vector>

namespace mge {
	class Blob;
}

namespace sto {
	class SerializableComponent;

	class SerializeComponent : public EntityComponent {
		public:
			SerializeComponent();
			virtual ~SerializeComponent();
			
			void registerComponent(SerializableComponent &component, bool fullonly);
			
			void serialize(mge::Blob &blob, bool full);
			void deserialize(mge::Blob &blob, bool full);
	
		private:
			typedef std::vector<SerializableComponent *> SerializableList;
			SerializableList partialcomps;
			SerializableList fullcomps;
	};
}

#endif
