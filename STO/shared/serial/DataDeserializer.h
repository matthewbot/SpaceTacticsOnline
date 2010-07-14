#ifndef STO_SHARED_DATADESERIALIZER_H
#define STO_SHARED_DATADESERIALIZER_H

#include "DataVisitor.h"

namespace mge {
	class Blob;
}

namespace sto {
	class DataDeserializer : public DataVisitor {
		public:
			DataDeserializer(mge::Blob &blob);
			virtual ~DataDeserializer();
			
			virtual void visit(bool &val);
			virtual void visit(char &val);
			virtual void visit(short &val);
			virtual void visit(int &val);
			virtual void visit(float &val, int magnitude=0);
			
		private:
			mge::Blob &blob;
	};
	
}

#endif
