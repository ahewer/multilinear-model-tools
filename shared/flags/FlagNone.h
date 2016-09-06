/****
   This file is part of the multilinear-model-tools.
   These tools are meant to derive a multilinear tongue model or
   PCA palate model from mesh data and work with it.

   Some code of the multilinear-model-tools is based on
   Timo Bolkart's work on statistical analysis of human face shapes,
   cf. https://sites.google.com/site/bolkartt/

   Copyright (C) 2016 Alexander Hewer

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

****/
#ifndef __FLAG_NONE_H__
#define __FLAG_NONE_H__


#include <string>
#include <stdexcept>

#include "TypeName.h"
#include "Flag.h"

/* Template class for a flag that accepts no arguments and serves the purpose
 * of a toggle
 */
class FlagNone : public Flag{

  public:

    /*-----------------------------------------------------------------------*/

    FlagNone(std::string id, bool& value) :
      Flag(id, true), value(value) {

    }

    /*-----------------------------------------------------------------------*/

    virtual void add_argument(const std::string& ) {

      throw std::runtime_error(
          "Flag --" + this->flagId +
        " does not accept any arguments."
        );

    }

    /*-----------------------------------------------------------------------*/
    
    virtual void mark_as_present() {
      this->flagPresent = true;
      this->value = true;
    }

    /*-----------------------------------------------------------------------*/

    bool is_set() const {
      return this->flagPresent;
    }

    /*-----------------------------------------------------------------------*/

    virtual bool is_valid() const {
      // flag is valid if either the flag is present or it is optional
      return (
      ( this->flagPresent ) ||
      ( this->flagOptional )
      );
    }

    /*-----------------------------------------------------------------------*/
    
    virtual std::string get_usage_string() const {

      std::string usage;
      usage = "--" + this->flagId;

      // mark optional flags with "[ ... ]"
      if( this->flagOptional == true ) {
        usage = "[ " + usage + " ]";
      }

      return usage;

    }

    /*-----------------------------------------------------------------------*/

    bool& value;

};
#endif
