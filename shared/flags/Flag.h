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
#ifndef __FLAG_H__
#define __FLAG_H__

#include <string>

/* Abstract base class for a flag */
class Flag{
  public:

    /*-----------------------------------------------------------------------*/

    Flag( std::string id, bool optional = false ) :
      flagId(id), flagOptional(optional) {

        this->argumentsRead = false;
        this->flagPresent = false;

      }

    /*-----------------------------------------------------------------------*/

    virtual std::string get_id() const {
      return this->flagId;
    }

    /*-----------------------------------------------------------------------*/

    virtual void mark_as_present() {
      this->flagPresent = true;
    }

    /*-----------------------------------------------------------------------*/

    bool is_optional() const {
      return this->flagOptional;
    }

    /*-----------------------------------------------------------------------*/

    bool is_present() const {
      return this->flagPresent;
    }

    /*-----------------------------------------------------------------------*/

    virtual void add_argument(const std::string& value ) = 0;
    virtual bool is_valid() const = 0;
    virtual std::string get_usage_string() const = 0;

    /*-----------------------------------------------------------------------*/

  protected:

    /*-----------------------------------------------------------------------*/

    Flag(){
      this->flagOptional = false;
      this->argumentsRead = false;
      this->flagPresent = false;
    }

    /*-----------------------------------------------------------------------*/

    std::string flagId;
    bool flagOptional;
    bool argumentsRead;
    bool flagPresent;
};
#endif
