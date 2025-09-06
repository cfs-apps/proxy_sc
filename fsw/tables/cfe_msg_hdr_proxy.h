/*
**  Copyright 2022 bitValence, Inc.
**  All Rights Reserved.
**
**  This program is free software; you can modify and/or redistribute it
**  under the terms of the GNU Affero General Public License
**  as published by the Free Software Foundation; version 3 with
**  attribution addendums as found in the LICENSE.txt
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU Affero General Public License for more details.
**
**  Purpose:
**    Define cFE Message module macros that allow apps compliant with
**    the cFE equuleus-rc1 release to be integrated with Basecamp
**
*/

/**
 * @file
 *
 * Define the following macros to be compatible with Basecamp's cFE version
 *  - CFE_MSG_CMD_HDR_SEC_INIT()
 *  - CFE_MSG_CMD_HDR_INIT()
 */

#ifndef DEFAULT_CFE_MSG_HDR_PRI_H
#define DEFAULT_CFE_MSG_HDR_PRI_H


/**
 * \brief Macro to initialize secondary header, used in macro to intialize entire header which is useful in tables
 */
#define CFE_MSG_CMD_HDR_SEC_INIT(fc, cksum) .Sec = {.FunctionCode = (fc), .Checksum = (cksum)}


/**
 * \brief Macro to initialize a command header, useful in tables that define commands
 */

/* bc: Original macro
#define CFE_MSG_CMD_HDR_INIT(mid, size, fc, cksum)                       \
     {                                                                    \
         .CommandHeader.Message.CCSDS =                                                     \
             {                                                            \
                 .CommonHdr = {.AppId    = {((mid) >> 8) & 0xFF, (mid)&0xFF},   \
                               .Sequence = {0xC0, 0},                           \
                               .Length   = {((size)-7) >> 8, ((size)-7) & 0xFF}}, \
             },                                                           \
         CFE_MSG_CMD_HDR_SEC_INIT(fc, cksum)                              \
     }
*/

/*
** Updated structures based on:
**    cfe_tbl_eds_typedef.h: CFE_TBL_CommandBase_t
**    cfe_hdr_eds_typedef.h: CFE_HDR_CommandHeader_t
**    ccsds_spacepacket_eds_typedefs.h: struct CCSDS_CommonHdr
**
** Removed CFE_MSG_CMD_HDR_SEC_INIT() since this proxy is for
** one use case and doesn't require general cFE structure.
*/

#define CFE_MSG_CMD_HDR_INIT(mid, size, fc, cksum)          \
    {                                                       \
        .CmdHeader =          \
            {                                               \
                .Message.CCSDS.CommonHdr = {                              \
                              .AppId    = ((mid) >> 8),     \
                              .Sequence = (0xC0),           \
                              .Length   = (((size)-7) >> 8) \
                             },                             \
                .Sec = {                                    \
                              .FunctionCode = (fc),         \
                              .Checksum = (cksum)           \
                       }                                    \
            },                                              \
    }

#define CFE_MSG_CMD_BUF_INIT(mid, size, fc, cksum) \
    {(((mid) >> 8) & 0xFF),((mid)&0xFF),0xC0,0,(((size)-7) >> 8),(((size)-7) & 0xFF),0,fc,(((cksum) >> 8) & 0xFF),((cksum)&0xFF),0,0,0,0,0,0}











#endif /* DEFAULT_CFE_MSG_HDR_PRI_H */




