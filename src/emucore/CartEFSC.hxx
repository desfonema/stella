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

#ifndef CARTRIDGEEFSC_HXX
#define CARTRIDGEEFSC_HXX

class System;

#include "bspf.hxx"
#include "Cart.hxx"
#ifdef DEBUGGER_SUPPORT
  #include "CartEFSCWidget.hxx"
#endif

/**
  Cartridge class used for Homestar Runner by Paul Slocum.
  There are 16 4K banks (total of 64K ROM) with 128 bytes of RAM.
  Accessing $1FE0 - $1FEF switches to each bank.
  RAM read port is $1080 - $10FF, write port is $1000 - $107F.

  @author  Stephen Anthony
*/
class CartridgeEFSC : public Cartridge
{
  friend class CartridgeEFSCWidget;

  public:
    /**
      Create a new cartridge using the specified image

      @param image     Pointer to the ROM image
      @param size      The size of the ROM image
      @param md5       The md5sum of the ROM image
      @param settings  A reference to the various settings (read-only)
    */
    CartridgeEFSC(const BytePtr& image, uInt32 size, const string& md5,
                  const Settings& settings);
    virtual ~CartridgeEFSC() = default;

  public:
    /**
      Reset device to its power-on state
    */
    void reset() override;

    /**
      Install cartridge in the specified system.  Invoked by the system
      when the cartridge is attached to it.

      @param system The system the device should install itself in
    */
    void install(System& system) override;

    /**
      Install pages for the specified bank in the system.

      @param bank The bank that should be installed in the system
    */
    bool bank(uInt16 bank) override;

    /**
      Get the current bank.
    */
    uInt16 getBank() const override;

    /**
      Query the number of banks supported by the cartridge.
    */
    uInt16 bankCount() const override;

    /**
      Patch the cartridge ROM.

      @param address  The ROM address to patch
      @param value    The value to place into the address
      @return    Success or failure of the patch operation
    */
    bool patch(uInt16 address, uInt8 value) override;

    /**
      Access the internal ROM image for this cartridge.

      @param size  Set to the size of the internal ROM image data
      @return  A pointer to the internal ROM image data
    */
    const uInt8* getImage(uInt32& size) const override;

    /**
      Save the current state of this cart to the given Serializer.

      @param out  The Serializer object to use
      @return  False on any errors, else true
    */
    bool save(Serializer& out) const override;

    /**
      Load the current state of this cart from the given Serializer.

      @param in  The Serializer object to use
      @return  False on any errors, else true
    */
    bool load(Serializer& in) override;

    /**
      Get a descriptor for the device name (used in error checking).

      @return The name of the object
    */
    string name() const override { return "CartridgeEFSC"; }

  #ifdef DEBUGGER_SUPPORT
    /**
      Get debugger widget responsible for accessing the inner workings
      of the cart.
    */
    CartDebugWidget* debugWidget(GuiObject* boss, const GUI::Font& lfont,
        const GUI::Font& nfont, int x, int y, int w, int h) override
    {
      return new CartridgeEFSCWidget(boss, lfont, nfont, x, y, w, h, *this);
    }
  #endif

  public:
    /**
      Get the byte at the specified address.

      @return The byte at the specified address
    */
    uInt8 peek(uInt16 address) override;

    /**
      Change the byte at the specified address to the given value

      @param address The address where the value should be stored
      @param value The value to be stored at the address
      @return  True if the poke changed the device address space, else false
    */
    bool poke(uInt16 address, uInt8 value) override;

  private:
    // The 64K ROM image of the cartridge
    uInt8 myImage[65536];

    // The 128 bytes of RAM
    uInt8 myRAM[128];

    // Indicates the offset into the ROM image (aligns to current bank)
    uInt16 myBankOffset;

  private:
    // Following constructors and assignment operators not supported
    CartridgeEFSC() = delete;
    CartridgeEFSC(const CartridgeEFSC&) = delete;
    CartridgeEFSC(CartridgeEFSC&&) = delete;
    CartridgeEFSC& operator=(const CartridgeEFSC&) = delete;
    CartridgeEFSC& operator=(CartridgeEFSC&&) = delete;
};

#endif
