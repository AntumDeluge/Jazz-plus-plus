/*
**  jazz - a midi sequencer for Linux
**
**  Copyright (C) 1994 Andreas Voss (andreas@avix.rhein-neckar.de)
**
**  Portions Copyright (C) 1995 Per Sigmond (Per.Sigmond@hia.no)
**
**  This program is free software; you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation; either version 2 of the License, or
**  (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/
 
/* midi_p.x - midinet protocol specification - Written by Per Sigmond, HiA */

typedef opaque midi_buf<>;

program MIDINET_PROG {
	version MIDINET_VERS {
		int mpu_write_ack( midi_buf ) = 1;
		void mpu_write_noack( midi_buf ) = 2;
	} = 1;
} = 0x40000001;
