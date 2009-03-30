/* -*- Mode: C++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 1998
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef __PLUGIN_H__
#define __PLUGIN_H__

/* Xlib/Xt stuff */
#include <X11/Xlib.h>
#include <X11/Intrinsic.h>
#include <X11/cursorfont.h>
#include <GL/glx.h>

#include <iostream>
#include <sstream>

#include "pluginbase.h"
#include "swf.h"
#include "streams.h"

class nsPluginInstance : public nsPluginInstanceBase
{
public:
  nsPluginInstance(NPP aInstance);
  virtual ~nsPluginInstance();

  NPBool init(NPWindow* aWindow);
  void shut();
  NPBool isInitialized() {return mInitialized;}
  NPError GetValue(NPPVariable variable, void *value);
  NPError SetWindow(NPWindow* aWindow);
  NPError NewStream(NPMIMEType type, NPStream* stream, NPBool seekable, uint16* stype); 
  int32   Write(NPStream *stream, int32 offset, int32 len, void *buffer);

  // locals
  const char * getVersion();
  void draw();

private:
  NPP mInstance;
  NPBool mInitialized;

  Window mWindow;
  Display *mDisplay;
  Widget mXtwidget;
  int mX, mY;
  int mWidth, mHeight;
  Visual* mVisual;
  Colormap mColormap;
  unsigned int mDepth;
  XFontStruct *mFontInfo;
  GC mGC;

  GLXFBConfig mFBConfig;
  GLXContext mContext;

  std::istream swf_stream;
  sync_stream swf_buf;

  ParseThread pt;
  InputThread it;

};

#endif // __PLUGIN_H__
