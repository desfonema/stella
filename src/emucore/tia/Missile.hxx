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
// Copyright (c) 1995-2016 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//
// $Id$
//============================================================================

#ifndef TIA_6502TS_CORE_MISSILE
#define TIA_6502TS_CORE_MISSILE

#include "Serializable.hxx"
#include "bspf.hxx"
#include "Player.hxx"

class Missile : public Serializable
{
  public:
    Missile(uInt32 collisionMask);

  public:

    void reset();

    void enam(uInt8 value);

    void hmm(uInt8 value);

    void resm(bool hblank);

    void resmp(uInt8 value, const Player& player);

    void nusiz(uInt8 value);

    void startMovement();

    bool movementTick(uInt32 clock, bool apply);

    void render();

    void tick(bool isReceivingMclock = true);

    void setColor(uInt8 color);

    void setDebugColor(uInt8 color);
    void enableDebugColors(bool enabled);

    void toggleCollisions(bool enabled);

    void toggleEnabled(bool enabled);

    uInt8 getPixel(uInt8 colorIn) const {
      return (collision & 0x8000) ? myColor : colorIn;
    }

    /**
      Serializable methods (see that class for more information).
    */
    bool save(Serializer& out) const override;
    bool load(Serializer& in) override;
    string name() const override { return "TIA_Missile"; }

  public:

    uInt32 collision;

  private:

    void updateEnabled();
    void applyColors();

  private:

    uInt32 myCollisionMaskDisabled;
    uInt32 myCollisionMaskEnabled;

    bool myIsEnabled;
    bool myIsSuppressed;
    bool myEnam;
    uInt8 myResmp;

    uInt8 myHmmClocks;
    uInt8 myCounter;
    bool myIsMoving;
    uInt8 myWidth;
    uInt8 myEffectiveWidth;
    uInt8 myLastMovementTick;

    bool myIsRendering;
    Int8 myRenderCounter;

    const uInt8* myDecodes;

    uInt8 myColor;
    uInt8 myObjectColor, myDebugColor;
    bool myDebugEnabled;

  private:
    Missile(const Missile&) = delete;
    Missile(Missile&&) = delete;
    Missile& operator=(const Missile&) = delete;
    Missile& operator=(Missile&&) = delete;
};

#endif // TIA_6502TS_CORE_MISSILE