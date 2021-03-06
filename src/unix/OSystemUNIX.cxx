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

#include <cstdlib>

#include "FSNode.hxx"
#include "Version.hxx"
#include "OSystemUNIX.hxx"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void OSystemUNIX::getBaseDirAndConfig(string& basedir, string& cfgfile,
        string& savedir, string& loaddir,
        bool useappdir, const string& usedir)
{
  // Use XDG_CONFIG_HOME if defined, otherwise use the default
  const char* configDir = getenv("XDG_CONFIG_HOME");
  if(configDir == nullptr)  configDir = "~/.config";
  basedir = string(configDir) + "/stella";
  savedir = loaddir = "~/";

  // Check to see if basedir overrides are active
  if(useappdir)
    cout << "ERROR: base dir in app folder not supported" << endl;
  else if(usedir != "")
  {
    basedir = FilesystemNode(usedir).getPath();
    savedir = loaddir = basedir;
  }

  // (Currently) non-documented alternative for using version-specific
  // config file
  ostringstream buf;
  buf << basedir << "/stellarc" << "-" << STELLA_VERSION;

  // Use version-specific config file only if it already exists
  FilesystemNode altConfigFile(buf.str());
  if(altConfigFile.exists() && altConfigFile.isWritable())
    cfgfile = altConfigFile.getPath();
  else
    cfgfile = basedir + "/stellarc";
}
