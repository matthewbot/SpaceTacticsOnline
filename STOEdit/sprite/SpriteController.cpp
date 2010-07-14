#include "SpriteController.h"
#include "ColorView.h"
#include "NormalView.h"
#include "DepthView.h"
#include "GameView.h"
#include <STOEdit/core/TextInputDialog.h>
#include <STOEdit/core/TextInputDialogCallback.h>
#include <STOEdit/core/MessageDialog.h>
#include <STOEdit/core/ViewFactory.h>
#include <STOEdit/core/WorkSpace.h>
#include <STOEdit/core/PaneManager.h>
#include <STOEdit/core/Pane.h>
#include <STOEdit/input/InputEvent.h>
#include <MGE/res/Font.h>
#include <MGE/util/Exception.h>
#include <boost/scoped_ptr.hpp>
#include <cassert>

using namespace stoedit;
using namespace mge;
using namespace boost;
using namespace std;

SpriteController::SpriteController(TextureManager &texman, WorkSpace &workspace) : data(texman), workspace(workspace) { }
SpriteController::~SpriteController() { }

namespace {
	template <class ViewT> struct AbstractViewFactory : public ViewFactory {
		SpriteData &data;
		const SpriteControllerRes &spriteres;
	
		AbstractViewFactory(SpriteData &data, const SpriteControllerRes &spriteres) : data(data), spriteres(spriteres) { }
		virtual ~AbstractViewFactory() { }
		
		virtual auto_ptr<View> makeView(ViewProperties &props, int width, int height) {
			return auto_ptr<View>(new ViewT(props, width, height, data, spriteres));
		}
	};
}

ViewFactory *SpriteController::getViewFactory(int num) {
	switch (num) {
		case 1:
			return new AbstractViewFactory<ColorView>(data, spriteres);
		
		case 2:
			return new AbstractViewFactory<DepthView>(data, spriteres);
		
		case 3:
			return new AbstractViewFactory<NormalView>(data, spriteres);
		
		case 4:
			return new AbstractViewFactory<GameView>(data, spriteres);
		
		default:
			return NULL;
	}
}

struct SpriteController::OpenSaveTextViewCallback : public TextInputDialogCallback {
	SpriteController &con;
	
	typedef void (SpriteData:: *OpenSaveFunc)(const string &);
	OpenSaveFunc opensave;

	OpenSaveTextViewCallback(SpriteController &con, OpenSaveFunc opensave) : con(con), opensave(opensave) { }

	virtual void gotInput(const string &input) {
		try {
			(con.data.*opensave)(input);
		} catch (Exception &ex) {
			con.workspace.getDialogManager().setDialog(new MessageDialog(con.spriteres.dialogfont, "Couldn't open file.", 200));
		}	
	}
	
	virtual void gotCancel() { }
};

bool SpriteController::gotEvent(const InputEvent &event) {
	if (event.getType() == InputEvent::KEY_PRESSED || event.getType() == InputEvent::KEY_RELEASED) {
		if (event.getKey() == 'o') {
			if (event.getType() == InputEvent::KEY_PRESSED) {
				OpenSaveTextViewCallback *callback = new OpenSaveTextViewCallback(*this, &SpriteData::openSet);
				workspace.getDialogManager().setDialog(new TextInputDialog(callback, spriteres.dialogfont, "File name to open (escape to cancel)", 300));
			}
		
			return true;
		} else if (event.getKey() == 's') {
			if (event.getType() == InputEvent::KEY_PRESSED) {
				OpenSaveTextViewCallback *callback = new OpenSaveTextViewCallback(*this, &SpriteData::saveSet);
				workspace.getDialogManager().setDialog(new TextInputDialog(callback, spriteres.dialogfont, "File name to save (escape to cancel)", 300));
			}
			
			return true;
		} else if (event.getKey() == 't') {
			if (event.getType() == InputEvent::KEY_PRESSED) {
				workspace.getDialogManager().setDialog(new TextInputDialog(NULL, spriteres.dialogfont, "foo bar?", 300));
			}
		} else if (event.getKey() >= '0' || event.getKey() <= '9') {
			int viewnum = event.getKey() - '0';
			
			scoped_ptr<ViewFactory> fact(getViewFactory(viewnum));
			Pane *pane = workspace.getPanes().getSelectedPane();
			
			if (fact && pane) 
				pane->setView(*fact);
			
			return true;
		}
	}
	
	return false;
}
