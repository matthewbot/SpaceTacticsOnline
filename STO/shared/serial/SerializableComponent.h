#ifndef STO_SHARED_SERIALIZEABLECOMPONENT_H
#define STO_SHARED_SERIALIZEABLECOMPONENT_H

namespace mge {
	class Blob;
}

namespace sto {
	class DataVisitor;

	class SerializableComponent {
		public:
			SerializableComponent();
			virtual ~SerializableComponent();
			
			void serialize(mge::Blob &blob);
			void deserialize(mge::Blob &blob);
			
		protected:
			virtual void visitData(DataVisitor &visit) = 0;
	};
}

#endif
