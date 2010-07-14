#ifndef STOEDIT_TEXTINPUTDIALOGCALLBACK_H
#define STOEDIT_TEXTINPUTDIALOGCALLBACK_H

namespace stoedit {
	class TextInputDialogCallback {
		public:
			inline virtual ~TextInputDialogCallback() { }
			
			virtual void gotInput(const std::string &input) = 0;
			virtual void gotCancel() = 0;
	};
}

#endif
