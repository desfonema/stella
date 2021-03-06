//============================================================================
//
//   SSSS    tt          lll  lll
//  SS  SS   tt           ll   ll
//  SS     tttttt  eeee   ll   ll   aaaa
//   SSSS    tt   ee  ee  ll   ll      aa
//      SS   tt   eeeeee  ll   ll   aaaaa  --  "An Atari 2600 VCS Emulator"
//  SS  SS   tt   ee      ll   ll  aa  aa
//   SSSS     ttt  eeeee llll llll  aaaaa
//
// Copyright (c) 1995-2019 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//============================================================================

#ifndef ROM_INFO_WIDGET_HXX
#define ROM_INFO_WIDGET_HXX

class FBSurface;
class Properties;
namespace GUI {
  struct Size;
}

#include "Widget.hxx"
#include "bspf.hxx"

class RomInfoWidget : public Widget
{
  public:
    RomInfoWidget(GuiObject *boss, const GUI::Font& font,
                  int x, int y, int w, int h);
    virtual ~RomInfoWidget() = default;

    void setProperties(const Properties& props, const FilesystemNode& node);
    void clearProperties();
    void reloadProperties(const FilesystemNode& node);

  protected:
    void drawWidget(bool hilite) override;

  private:
    void parseProperties(const FilesystemNode& node);

  private:
    // Surface pointer holding the PNG image
    shared_ptr<FBSurface> mySurface;

    // Whether the surface should be redrawn by drawWidget()
    bool mySurfaceIsValid;

    // Some ROM properties info, as well as 'tEXt' chunks from the PNG image
    StringList myRomInfo;

    // The properties for the currently selected ROM
    Properties myProperties;

    // Indicates if the current properties should actually be used
    bool myHaveProperties;

    // Indicates if an error occurred in creating/displaying the surface
    string mySurfaceErrorMsg;

    // How much space available for the PNG image
    GUI::Size myAvail;

  private:
    // Following constructors and assignment operators not supported
    RomInfoWidget() = delete;
    RomInfoWidget(const RomInfoWidget&) = delete;
    RomInfoWidget(RomInfoWidget&&) = delete;
    RomInfoWidget& operator=(const RomInfoWidget&) = delete;
    RomInfoWidget& operator=(RomInfoWidget&&) = delete;
};

#endif
