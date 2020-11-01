/*
 * Copyright (C) 2020  Joshua Minter
 *
 * This file is part of ReplaySorcery.
 *
 * ReplaySorcery is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ReplaySorcery is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ReplaySorcery.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "device.h"
#include "../config.h"

void rsDeviceDestroy(RSDevice **device) {
   if (*device != NULL && (*device)->destroy != NULL) {
      (*device)->destroy(*device);
   }
   av_freep(device);
}

int rsVideoDeviceCreate(RSDevice **device) {
   int ret;
   switch (rsConfig.videoInput) {
   case RS_CONFIG_DEVICE_X11:
      return rsX11DeviceCreate(device);
   }

   if ((ret = rsX11DeviceCreate(device)) >= 0) {
      av_log(NULL, AV_LOG_INFO, "Created X11 device\n");
      return 0;
   }
   av_log(NULL, AV_LOG_WARNING, "Failed to create X11 device: %s\n", av_err2str(ret));

   return AVERROR(ENOSYS);
}
