#ifndef STO_SHARED_INIT_H
#define STO_SHARED_INIT_H

namespace mge {
	class ResourceSystem;
}

namespace sto {
	class EntityBuilderFactory;

	EntityBuilderFactory *initSharedEntityBuilder(mge::ResourceSystem &res);
}

#endif
