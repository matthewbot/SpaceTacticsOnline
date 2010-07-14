#ifndef STO_SHARED_DATAVISITOR_H
#define STO_SHARED_DATAVISITOR_H

namespace sto {
	class DataVisitor {
		public:
			inline virtual ~DataVisitor() { }
			
			virtual void visit(bool &val) =0;
			virtual void visit(char &val) =0;
			virtual void visit(short &val) =0;
			virtual void visit(int &val) =0;
			virtual void visit(float &val, int magnitude=0) =0;
	};
}

#endif
