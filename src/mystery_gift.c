#include "global.h"
#include "main.h"
#include "text.h"
#include "task.h"
#include "alloc.h"
#include "gpu_regs.h"
#include "scanline_effect.h"
#include "text_window.h"
#include "bg.h"
#include "window.h"
#include "strings.h"
#include "text_window.h"
#include "menu.h"
#include "palette.h"
#include "constants/songs.h"
#include "sound.h"
#include "mystery_gift.h"
#include "union_room.h"
#include "title_screen.h"
#include "ereader_screen.h"
#include "international_string_util.h"
#include "list_menu.h"
#include "string_util.h"
#include "mevent.h"
#include "mevent_801BAAC.h"
#include "save.h"
#include "link.h"
#include "mevent_server_ish.h"
#include "event_data.h"
#include "link_rfu.h"
#include "mevent_news.h"
#include "mevent_server.h"

void bgid_upload_textbox_1(u8 bgId);
void task_add_00_mystery_gift(void);
void task00_mystery_gift(u8 taskId);

EWRAM_DATA u8 gUnknown_02022C58[2] = {};

const u16 gUnkTextboxBorderPal[] = INCBIN_U16("graphics/interface/unk_textbox_border.gbapal");
const u32 gUnkTextboxBorderGfx[] = INCBIN_U32("graphics/interface/unk_textbox_border.4bpp.lz");

struct MysteryGiftTaskData
{
    u16 unk0;
    u16 unk2;
    u16 unk4;
    u16 unk6;
    u8 unk8;
    u8 unk9;
    u8 unkA;
    u8 unkB;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 * unk10;
};

const struct BgTemplate gUnknown_082F0598[] = {
    {
        .bg = 0,
        .charBaseIndex = 2,
        .mapBaseIndex = 15,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0x000
    }, {
        .bg = 1,
        .charBaseIndex = 0,
        .mapBaseIndex = 14,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0x000
    }, {
        .bg = 2,
        .charBaseIndex = 0,
        .mapBaseIndex = 13,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0x000
    }, {
        .bg = 3,
        .charBaseIndex = 0,
        .mapBaseIndex = 12,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 3,
        .baseTile = 0x000
    }
};

const struct WindowTemplate gUnknown_082F05A8[] = {
    {
        .bg = 0x00,
        .tilemapLeft = 0x00,
        .tilemapTop = 0x00,
        .width = 0x1e,
        .height = 0x02,
        .paletteNum = 0x0c,
        .baseBlock = 0x0013
    }, {
        .bg = 0x00,
        .tilemapLeft = 0x01,
        .tilemapTop = 0x0f,
        .width = 0x1c,
        .height = 0x04,
        .paletteNum = 0x0c,
        .baseBlock = 0x004f
    }, {
        .bg = 0x00,
        .tilemapLeft = 0x00,
        .tilemapTop = 0x0f,
        .width = 0x1e,
        .height = 0x05,
        .paletteNum = 0x0d,
        .baseBlock = 0x004f
    }, {
        0xFF
    }
};

const struct WindowTemplate gUnknown_082F05C8 = {
    .bg = 0x00,
    .tilemapLeft = 0x01,
    .tilemapTop = 0x0f,
    .width = 0x1c,
    .height = 0x04,
    .paletteNum = 0x0c,
    .baseBlock = 0x00e5
};

const struct WindowTemplate gUnknown_082F05D0 = {
    .bg = 0x00,
    .tilemapLeft = 0x01,
    .tilemapTop = 0x0f,
    .width = 0x14,
    .height = 0x04,
    .paletteNum = 0x0c,
    .baseBlock = 0x00e5
};

const struct WindowTemplate gUnknown_082F05D8 = {
    .bg = 0x00,
    .tilemapLeft = 0x01,
    .tilemapTop = 0x0f,
    .width = 0x13,
    .height = 0x04,
    .paletteNum = 0x0c,
    .baseBlock = 0x00e5
};

const struct WindowTemplate gUnknown_082F05E0 = {
    .bg = 0x00,
    .tilemapLeft = 0x08,
    .tilemapTop = 0x06,
    .width = 0x0e,
    .height = 0x06,
    .paletteNum = 0x0c,
    .baseBlock = 0x0155
};

const struct WindowTemplate gUnknown_082F05E8 = {
    .bg = 0x00,
    .tilemapLeft = 0x17,
    .tilemapTop = 0x0f,
    .width = 0x06,
    .height = 0x04,
    .paletteNum = 0x0c,
    .baseBlock = 0x0155
};

const struct WindowTemplate gUnknown_082F05F0 = {
    .bg = 0x00,
    .tilemapLeft = 0x16,
    .tilemapTop = 0x0b,
    .width = 0x07,
    .height = 0x08,
    .paletteNum = 0x0c,
    .baseBlock = 0x0155
};

const struct WindowTemplate gUnknown_082F05F8 = {
    .bg = 0x00,
    .tilemapLeft = 0x16,
    .tilemapTop = 0x0d,
    .width = 0x07,
    .height = 0x06,
    .paletteNum = 0x0c,
    .baseBlock = 0x0155
};

const struct WindowTemplate gUnknown_082F0600 = {
    .bg = 0x00,
    .tilemapLeft = 0x16,
    .tilemapTop = 0x0f,
    .width = 0x07,
    .height = 0x04,
    .paletteNum = 0x0c,
    .baseBlock = 0x0155
};

const struct ListMenuItem gUnknown_082F0608[] = {
    { gText_WonderCards,  0 },
    { gText_WonderNews,   1 },
    { gText_Exit3,       -2 }
};

const struct ListMenuItem gUnknown_082F0620[] = {
    { gText_WirelessCommunication,  0 },
    { gText_Friend2,                1 },
    { gText_Cancel2,               -2 }
};

const struct ListMenuTemplate gUnknown_082F0638 = {
    .items = NULL,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .itemPrintFunc = NULL,
    .totalItems = 3,
    .maxShowed = 3,
    .windowId = 0,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = 0,
    .fontId = 1,
    .cursorKind = 0
};

const struct ListMenuItem gUnknown_082F0650[] = {
    { gText_Receive,  0 },
    { gText_Send,     1 },
    { gText_Toss,     2 },
    { gText_Cancel2, -2 }
};

const struct ListMenuItem gUnknown_082F0670[] = {
    { gText_Receive,  0 },
    { gText_Toss,     2 },
    { gText_Cancel2, -2 }
};

const struct ListMenuItem gUnknown_082F0688[] = {
    { gText_Receive,  0 },
    { gText_Send,     1 },
    { gText_Cancel2, -2 }
};

const struct ListMenuItem gUnknown_082F06A0[] = {
    { gText_Receive,  0 },
    { gText_Cancel2, -2 }
};

const struct ListMenuTemplate gUnknown_082F06B0 = {
    .items = gUnknown_082F0650,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .itemPrintFunc = NULL,
    .totalItems = 4,
    .maxShowed = 4,
    .windowId = 0,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = 0,
    .fontId = 1,
    .cursorKind = 0
};

const struct ListMenuTemplate gUnknown_082F06C8 = {
    .items = gUnknown_082F0670,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .itemPrintFunc = NULL,
    .totalItems = 3,
    .maxShowed = 3,
    .windowId = 0,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = 0,
    .fontId = 1,
    .cursorKind = 0
};

const struct ListMenuTemplate gUnknown_082F06E0 = {
    .items = gUnknown_082F0688,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .itemPrintFunc = NULL,
    .totalItems = 3,
    .maxShowed = 3,
    .windowId = 0,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = 0,
    .fontId = 1,
    .cursorKind = 0
};

const struct ListMenuTemplate gUnknown_082F06F8 = {
    .items = gUnknown_082F06A0,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .itemPrintFunc = NULL,
    .totalItems = 2,
    .maxShowed = 2,
    .windowId = 0,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = 0,
    .itemVerticalPadding = 0,
    .scrollMultiple = 0,
    .fontId = 1,
    .cursorKind = 0
};

const u8 *const Unref_082F0710[] = {
    gText_VarietyOfEventsImportedWireless,
    gText_WonderCardsInPossession,
    gText_ReadNewsThatArrived,
    gText_ReturnToTitle
};

ALIGNED(2) const u8 gUnknown_082F0720[] = { 0, 1, 2 };
ALIGNED(2) const u8 gUnknown_082F0724[] = { 0, 1, 2 };
ALIGNED(2) const u8 gUnknown_082F0728[] = { 1, 2, 3 };

void sub_8018424(void)
{
    ProcessSpriteCopyRequests();
    LoadOam();
    TransferPlttBuffer();
}

void sub_8018438(void)
{
    RunTasks();
    RunTextPrinters();
    AnimateSprites();
    BuildOamBuffer();
}

bool32 sub_8018450(s32 arg)
{
    switch (gMain.state)
    {
    case 0:
        SetVBlankCallback(NULL);
        ResetPaletteFade();
        ResetSpriteData();
        FreeAllSpritePalettes();
        ResetTasks();
        ScanlineEffect_Stop();
        ResetBgsAndClearDma3BusyFlags(0);

        InitBgsFromTemplates(0, gUnknown_082F0598, ARRAY_COUNT(gUnknown_082F0598));
        ChangeBgX(0, 0, 0);
        ChangeBgY(0, 0, 0);
        ChangeBgX(1, 0, 0);
        ChangeBgY(1, 0, 0);
        ChangeBgX(2, 0, 0);
        ChangeBgY(2, 0, 0);
        ChangeBgX(3, 0, 0);
        ChangeBgY(3, 0, 0);

        SetBgTilemapBuffer(3, Alloc(0x800));
        SetBgTilemapBuffer(2, Alloc(0x800));
        SetBgTilemapBuffer(1, Alloc(0x800));
        SetBgTilemapBuffer(0, Alloc(0x800));

        bgid_upload_textbox_1(3);
        InitWindows(gUnknown_082F05A8);
        DeactivateAllTextPrinters();
        ClearGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_WIN1_ON);
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 0);
        gMain.state++;
        break;
    case 1:
        LoadPalette(gUnkTextboxBorderPal, 0, 0x20);
        LoadPalette(stdpal_get(2), 0xd0, 0x20);
        sub_81978B0(0xC0);
        LoadUserWindowBorderGfx(0, 0xA, 0xE0);
        LoadUserWindowBorderGfx_(0, 0x1, 0xF0);
        FillBgTilemapBufferRect(0, 0x000, 0, 0, 32, 32, 0x11);
        FillBgTilemapBufferRect(1, 0x000, 0, 0, 32, 32, 0x11);
        FillBgTilemapBufferRect(2, 0x000, 0, 0, 32, 32, 0x11);
        sub_8018798(3);
        sub_80186EC(arg, 0);
        gMain.state++;
        break;
    case 2:
        CopyBgTilemapBufferToVram(3);
        CopyBgTilemapBufferToVram(2);
        CopyBgTilemapBufferToVram(1);
        CopyBgTilemapBufferToVram(0);
        gMain.state++;
        break;
    case 3:
        ShowBg(0);
        ShowBg(3);
        PlayBGM(MUS_RG_OKURIMONO);
        SetVBlankCallback(sub_8018424);
        EnableInterrupts(INTR_FLAG_VBLANK | INTR_FLAG_VCOUNT | INTR_FLAG_TIMER3 | INTR_FLAG_SERIAL);
        return TRUE;
    }

    return FALSE;
}

void c2_mystery_gift(void)
{
    if (sub_8018450(0))
    {
        SetMainCallback2(sub_8018438);
        gUnknown_02022C60 = FALSE;
        task_add_00_mystery_gift();
    }
    RunTasks();
}

void sub_801867C(void)
{
    if (sub_8018450(1))
    {
        SetMainCallback2(sub_8018438);
        gUnknown_02022C60 = TRUE;
        sub_81D5014();
    }
}

void sub_80186A4(void)
{
    gUnknown_02022C60 = FALSE;
    FreeAllWindowBuffers();
    Free(GetBgTilemapBuffer(0));
    Free(GetBgTilemapBuffer(1));
    Free(GetBgTilemapBuffer(2));
    Free(GetBgTilemapBuffer(3));
    SetMainCallback2(CB2_InitTitleScreen);
}

void sub_80186EC(bool8 isJapanese, bool32 usePickOkCancel)
{
    const u8 * header;
    const u8 * options;
    FillWindowPixelBuffer(0, 0);
    if (!isJapanese)
    {
        header = gText_MysteryGift;
        options = !usePickOkCancel ? gText_PickOKExit : gText_PickOKCancel;
    }
    else
    {
        header = gJPText_MysteryGift;
        options = gJPText_DecideStop;
    }

    AddTextPrinterParameterized4(0, 1, 4, 1, 0, 0, gUnknown_082F0720, -1, header);
    AddTextPrinterParameterized4(0, 0, GetStringRightAlignXOffset(0, options, 0xDE), 1, 0, 0, gUnknown_082F0720, -1, options);
    CopyWindowToVram(0, 2);
    PutWindowTilemap(0);
}

void sub_8018784(u8 windowId)
{
    sub_8098858(windowId, 0x01, 0xF);
}

void sub_8018798(u32 bg)
{
    s32 i = 0, j;

    FillBgTilemapBufferRect(bg, 0x003, 0, 0, 32, 2, 0x11);

    for (i = 0; i < 18; i++)
    {
        for (j = 0; j < 32; j++)
        {
            if ((i & 1) != (j & 1))
            {
                FillBgTilemapBufferRect(bg, 1, j, i + 2, 1, 1, 0x11);
            }
            else
            {
                FillBgTilemapBufferRect(bg, 2, j, i + 2, 1, 1, 0x11);
            }
        }
    }
}

void sub_8018838(bool32 arg)
{
    switch (arg)
    {
    case 0:
        FillBgTilemapBufferRect(0, 0, 0, 0, 32, 32, 0x11);
        break;
    case 1:
        FillBgTilemapBufferRect(0, 0, 0, 2, 32, 30, 0x11);
        break;
    }
    CopyBgTilemapBufferToVram(0);
}

void sub_8018884(const u8 *str)
{
    StringExpandPlaceholders(gStringVar4, str);
    FillWindowPixelBuffer(1, 0x11);
    AddTextPrinterParameterized4(1, 1, 0, 1, 0, 0, gUnknown_082F0728, 0, gStringVar4);
    sub_8098858(1, 0x001, 0xF);
    PutWindowTilemap(1);
    CopyWindowToVram(1, 3);
}

void sub_80188DC(void)
{
    rbox_fill_rectangle(1);
    ClearWindowTilemap(1);
    CopyWindowToVram(1, 1);
}

bool32 mevent_0814257C(u8 *textState, const u8 *str)
{
    switch (*textState)
    {
    case 0:
        sub_8018884(str);
        goto inc;
    case 1:
        DrawDownArrow(1, 0xD0, 0x14, 1, FALSE, &gUnknown_02022C58[0], &gUnknown_02022C58[1]);
        if (({gMain.newKeys & (A_BUTTON | B_BUTTON);}))
        {
        inc:
            (*textState)++;
        }
        break;
    case 2:
        DrawDownArrow(1, 0xD0, 0x14, 1, TRUE, &gUnknown_02022C58[0], &gUnknown_02022C58[1]);
        *textState = 0;
        sub_80188DC();
        return TRUE;
    case 0xFF:
        *textState = 2;
        break;
    }
    return FALSE;
}

void sub_801898C(void)
{
    DrawDownArrow(1, 0xD0, 0x14, 1, FALSE, &gUnknown_02022C58[0], &gUnknown_02022C58[1]);
}

void sub_80189B4(void)
{
    DrawDownArrow(1, 0xD0, 0x14, 1, TRUE, &gUnknown_02022C58[0], &gUnknown_02022C58[1]);
}

bool32 sub_80189DC(u8 * textState)
{
    switch (*textState)
    {
    case 0:
        sub_801898C();
        if (({gMain.newKeys & (A_BUTTON | B_BUTTON);}))
        {
            (*textState)++;
        }
        break;
    case 1:
        sub_80189B4();
        *textState = 0;
        return TRUE;
    }
    return FALSE;
}

bool32 sub_8018A1C(u8 * counter, const u8 * str)
{
    if (*counter == 0)
    {
        sub_8018884(str);
    }
    if (++(*counter) > 120)
    {
        *counter = 0;
        sub_80188DC();
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

u32 sub_8018A50(u8 * unused0, u16 * unused1, bool8 r2)
{
    struct ListMenuTemplate listMenuTemplate = gUnknown_082F0638;
    struct WindowTemplate windowTemplate = gUnknown_082F05E0;
    s32 r3;
    s32 r4;

    if (r2 == FALSE)
    {
        listMenuTemplate.items = gUnknown_082F0608;
    }
    else
    {
        listMenuTemplate.items = gUnknown_082F0620;
    }
    r3 = sub_81DB41C(&listMenuTemplate);
    if (r3 & 1)
    {
        r3++;
    }
    windowTemplate.width = r3;
    if (r3 < 30)
    {
        windowTemplate.tilemapLeft = (30 - r3) / 2;
    }
    else
    {
        windowTemplate.tilemapLeft = 0;
    }
    r4 = DoMysteryGiftListMenu(&windowTemplate, &listMenuTemplate, 1, 0x00A, 0xE0);
    if (r4 != -1)
    {
        ClearWindowTilemap(2);
        CopyWindowToVram(2, 1);
    }
    return r4;
}

s8 sub_8018B08(u8 * textState, u16 * windowId, bool8 r6, const u8 * str)
{
    struct WindowTemplate windowTemplate;
    s8 input;

    switch (*textState)
    {
    case 0:
        StringExpandPlaceholders(gStringVar4, str);
        if (r6 == 0)
        {
            *windowId = AddWindow(&gUnknown_082F05C8);
        }
        else
        {
            *windowId = AddWindow(&gUnknown_082F05D0);
        }
        FillWindowPixelBuffer(*windowId, 0x11);
        AddTextPrinterParameterized4(*windowId, 1, 0, 1, 0, 0, gUnknown_082F0728, 0, gStringVar4);
        sub_8098858(*windowId, 0x001, 0x0F);
        CopyWindowToVram(*windowId, 2);
        PutWindowTilemap(*windowId);
        (*textState)++;
        break;
    case 1:
        windowTemplate = gUnknown_082F05E8;
        if (r6 == 0)
        {
            windowTemplate.tilemapTop = 9;
        }
        else
        {
            windowTemplate.tilemapTop = 15;
        }
        CreateYesNoMenu(&windowTemplate, 10, 14, 0);
        (*textState)++;
        break;
    case 2:
        input = Menu_ProcessInputNoWrapClearOnChoose();
        if (input == -1 || input == 0 || input == 1)
        {
            *textState = 0;
            rbox_fill_rectangle(*windowId);
            ClearWindowTilemap(*windowId);
            CopyWindowToVram(*windowId, 1);
            RemoveWindow(*windowId);
            return input;
        }
        break;
    case 0xFF:
        *textState = 0;
        rbox_fill_rectangle(*windowId);
        ClearWindowTilemap(*windowId);
        CopyWindowToVram(*windowId, 1);
        RemoveWindow(*windowId);
        return -1;
    }

    return -2;
}

s32 sub_8018C4C(u8 * textState, u16 * windowId, bool32 r2, bool32 r3)
{
    struct WindowTemplate windowTemplate;
    s32 input;

    switch (*textState)
    {
    case 0:
        if (r2 == 0)
        {
            StringExpandPlaceholders(gStringVar4, gText_WhatToDoWithCards);
        }
        else
        {
            StringExpandPlaceholders(gStringVar4, gText_WhatToDoWithNews);
        }
        *windowId = AddWindow(&gUnknown_082F05D8);
        FillWindowPixelBuffer(*windowId, 0x11);
        AddTextPrinterParameterized4(*windowId, 1, 0, 1, 0, 0, gUnknown_082F0728, 0, gStringVar4);
        sub_8098858(*windowId, 0x001, 0x0F);
        CopyWindowToVram(*windowId, 2);
        PutWindowTilemap(*windowId);
        (*textState)++;
        break;
    case 1:
        windowTemplate = gUnknown_082F05E8;
        if (r3)
        {
            if (r2 == 0)
            {
                input = DoMysteryGiftListMenu(&gUnknown_082F05F8, &gUnknown_082F06C8, 1, 0x00A, 0xE0);
            }
            else
            {
                input = DoMysteryGiftListMenu(&gUnknown_082F0600, &gUnknown_082F06F8, 1, 0x00A, 0xE0);
            }
        }
        else
        {
            if (r2 == 0)
            {
                input = DoMysteryGiftListMenu(&gUnknown_082F05F0, &gUnknown_082F06B0, 1, 0x00A, 0xE0);
            }
            else
            {
                input = DoMysteryGiftListMenu(&gUnknown_082F05F8, &gUnknown_082F06E0, 1, 0x00A, 0xE0);
            }
        }
        if (input != -1)
        {
            *textState = 0;
            rbox_fill_rectangle(*windowId);
            ClearWindowTilemap(*windowId);
            CopyWindowToVram(*windowId, 1);
            RemoveWindow(*windowId);
            return input;
        }
        break;
    case 0xFF:
        *textState = 0;
        rbox_fill_rectangle(*windowId);
        ClearWindowTilemap(*windowId);
        CopyWindowToVram(*windowId, 1);
        RemoveWindow(*windowId);
        return -2;
    }

    return -1;
}

s32 sub_8018D98(bool32 a0)
{
    if (a0 == 0)
    {
        return sub_801B27C();
    }
    else
    {
        return sub_801B0CC();
    }
}

bool32 sub_8018DAC(u8 * state, bool32 arg1)
{
    s32 v0;

    switch (*state)
    {
    case 0:
        if (arg1 == 0)
        {
            sub_801BAAC(sav1_get_mevent_buffer_1(), sav1_get_mevent_buffer_2());
        }
        else
        {
            sub_801C6C8(sub_801B00C());
        }
        (*state)++;
        break;
    case 1:
        if (arg1 == 0)
        {
            v0 = sub_801BB74();
        check:
            if (v0 != 0)
            {
                goto done;
            }
            break;
        }
        else
        {
            v0 = sub_801C758();
            goto check;
        }
    done:
        *state = 0;
        return TRUE;
    }

    return FALSE;
}

bool32 sub_8018E08(bool32 arg0)
{
    if (arg0 == 0)
    {
        sub_801B1E8();
    }
    else
    {
        sub_801B06C();
    }
    return TRUE;
}

bool32 sub_8018E20(bool32 arg0, bool32 arg1)
{
    if (arg0 == 0)
    {
        if (sub_801BDA4(arg1) != 0)
        {
            sub_801BB48();
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
    else
    {
        if (sub_801CA50(arg1) != 0)
        {
            sub_801C72C();
            return TRUE;
        }
        else
        {
            return FALSE;
        }
    }
}

s32 sub_8018E50(u8 * textState, u16 * windowId, bool32 r2)
{
    if (r2 == 0)
    {
        return sub_8018B08(textState, windowId, TRUE, gText_IfThrowAwayCardEventWontHappen);
    }
    else
    {
        return sub_8018B08(textState, windowId, TRUE, gText_OkayToDiscardNews);
    }
}

bool32 mevent_message_was_thrown_away(u8 * textState, bool32 r1)
{
    if (r1 == 0)
    {
        return mevent_0814257C(textState, gText_WonderCardThrownAway);
    }
    else
    {
        return mevent_0814257C(textState, gText_WonderNewsThrownAway);
    }
}

bool32 mevent_save_game(u8 * state)
{
    switch (*state)
    {
    case 0:
        sub_8018884(gText_DataWillBeSaved);
        (*state)++;
        break;
    case 1:
        TrySavingData(0);
        (*state)++;
        break;
    case 2:
        sub_8018884(gText_SaveCompletedPressA);
        (*state)++;
        break;
    case 3:
        if (({gMain.newKeys & (A_BUTTON | B_BUTTON);}))
        {
            (*state)++;
        }
        break;
    case 4:
        *state = 0;
        sub_80188DC();
        return TRUE;
    }

    return FALSE;
}

const u8 * mevent_message(u32 * a0, u8 a1, u8 a2, u32 a3)
{
    const u8 * msg = NULL;
    *a0 = 0;

    switch (a3)
    {
    case 0:
        *a0 = 0;
        msg = gText_NothingSentOver;
        break;
    case 1:
        *a0 = 0;
        msg = gText_RecordUploadedViaWireless;
        break;
    case 2:
        *a0 = 1;
        msg = a2 == 0 ? gText_WonderCardReceived : gText_WonderCardReceivedFrom;
        break;
    case 3:
        *a0 = 1;
        msg = a2 == 0 ? gText_WonderNewsReceived : gText_WonderNewsReceivedFrom;
        break;
    case 4:
        *a0 = 1;
        msg = gText_NewStampReceived;
        break;
    case 5:
        *a0 = 0;
        msg = gText_AlreadyHadCard;
        break;
    case 6:
        *a0 = 0;
        msg = gText_AlreadyHadStamp;
        break;
    case 7:
        *a0 = 0;
        msg = gText_AlreadyHadNews;
        break;
    case 8:
        *a0 = 0;
        msg = gText_NoMoreRoomForStamps;
        break;
    case 9:
        *a0 = 0;
        msg = gText_CommunicationCanceled;
        break;
    case 10:
        *a0 = 0;
        msg = a1 == 0 ? gText_CantAcceptCardFromTrainer : gText_CantAcceptNewsFromTrainer;
        break;
    case 11:
        *a0 = 0;
        msg = gText_CommunicationError;
        break;
    case 12:
        *a0 = 1;
        msg = gText_NewTrainerReceived;
        break;
    case 13:
        *a0 = 1;
        break;
    case 14:
        *a0 = 0;
        break;
    }

    return msg;
}

bool32 mevent_08142CE8(u8 * state, const u8 * arg1, u16 * arg2)
{
    switch (*state)
    {
    case 0:
        if (arg1 != NULL)
        {
            sub_8018884(arg1);
        }
        PlayFanfare(MUS_FANFA4);
        *arg2 = 0;
        (*state)++;
        break;
    case 1:
        if (++(*arg2) > 0xF0)
        {
            (*state)++;
        }
        break;
    case 2:
        if (IsFanfareTaskInactive())
        {
            *state = 0;
            sub_80188DC();
            return TRUE;
        }
        break;
    }
    return FALSE;
}

const u8 * mevent_message_stamp_card_etc_send_status(u32 * a0, u8 unused, u32 state)
{
    const u8 * result = gText_CommunicationError;
    *a0 = 0;
    switch (state)
    {
    case 0:
        result = gText_NothingSentOver;
        break;
    case 1:
        result = gText_RecordUploadedViaWireless;
        break;
    case 2:
        result = gText_WonderCardSentTo;
        *a0 = 1;
        break;
    case 3:
        result = gText_WonderNewsSentTo;
        *a0 = 1;
        break;
    case 4:
        result = gText_StampSentTo;
        break;
    case 5:
        result = gText_OtherTrainerHasCard;
        break;
    case 6:
        result = gText_OtherTrainerHasStamp;
        break;
    case 7:
        result = gText_OtherTrainerHasNews;
        break;
    case 8:
        result = gText_NoMoreRoomForStamps;
        break;
    case 9:
        result = gText_OtherTrainerCanceled;
        break;
    case 10:
        result = gText_CantSendGiftToTrainer;
        break;
    case 11:
        result = gText_CommunicationError;
        break;
    case 12:
        result = gText_GiftSentTo;
        break;
    case 13:
        result = gText_GiftSentTo;
        break;
    case 14:
        result = gText_CantSendGiftToTrainer;
        break;
    }
    return result;
}

bool32 sub_8019174(u8 * state_p, u16 * arg1, u8 arg2, u32 state)
{
    u32 flag;
    const u8 * str = mevent_message_stamp_card_etc_send_status(&flag, arg2, state);
    if (flag)
    {
        return mevent_08142CE8(state_p, str, arg1);
    }
    else
    {
        return mevent_0814257C(state_p, str);
    }
}

void task_add_00_mystery_gift(void)
{
    u8 taskId = CreateTask(task00_mystery_gift, 0);
    struct MysteryGiftTaskData * data = (void *)gTasks[taskId].data;
    data->unk8 = 0;
    data->unk9 = 0;
    data->unkA = 0;
    data->unkB = 0;
    data->unkC = 0;
    data->unkD = 0;
    data->unk0 = 0;
    data->unk2 = 0;
    data->unk4 = 0;
    data->unk6 = 0;
    data->unkE = 0;
    data->unk10 = AllocZeroed(0x40);
}

void task00_mystery_gift(u8 taskId)
{
    struct MysteryGiftTaskData * data = (void *)gTasks[taskId].data;
    u32 sp0;
    const u8 * r1;

    switch (data->unk8)
    {
    case  0:
        data->unk8 = 1;
        break;
    case  1:
        switch (sub_8018A50(&data->unk9, &data->unk0, FALSE))
        {
        case 0:
            data->unkC = 0;
            if (sub_801B27C() == TRUE)
            {
                data->unk8 = 18;
            }
            else
            {
                data->unk8 = 2;
            }
            break;
        case 1:
            data->unkC = 1;
            if (sub_801B0CC() == TRUE)
            {
                data->unk8 = 18;
            }
            else
            {
                data->unk8 = 2;
            }
            break;
        case -2u:
            data->unk8 = 37;
            break;
        }
        break;
    case  2:
    {
        if (data->unkC == 0)
        {
            if (mevent_0814257C(&data->unk9, gText_DontHaveCardNewOneInput))
            {
                data->unk8 = 3;
                sub_80186EC(0, 1);
            }
        }
        else
        {
            if (mevent_0814257C(&data->unk9, gText_DontHaveNewsNewOneInput))
            {
                data->unk8 = 3;
                sub_80186EC(0, 1);
            }
        }
        break;
    }
    case  3:
        if (data->unkC == 0)
        {
            sub_8018884(gText_WhereShouldCardBeAccessed);
        }
        else
        {
            sub_8018884(gText_WhereShouldNewsBeAccessed);
        }
        data->unk8 = 4;
        break;
    case  4:
        switch (sub_8018A50(&data->unk9, &data->unk0, TRUE))
        {
        case 0:
            sub_80188DC();
            data->unk8 = 5;
            data->unkD = 0;
            break;
        case 1:
            sub_80188DC();
            data->unk8 = 5;
            data->unkD = 1;
            break;
        case -2u:
            sub_80188DC();
            if (sub_8018D98(data->unkC))
            {
                data->unk8 = 18;
            }
            else
            {
                data->unk8 = 0;
                sub_80186EC(0, 0);
            }
            break;
        }
        break;
    case  5:
    {
        register u8 eos asm("r1");
        gStringVar1[0] = (eos = EOS);
        gStringVar2[0] = eos;
        gStringVar3[0] = eos;
    }
        switch (data->unkC)
        {
        case 0:
            if (data->unkD == 1)
            {
                sub_8014EFC(0x15);
            }
            else if (data->unkD == 0)
            {
                sub_80152A8(0x15);
            }
            break;
        case 1:
            if (data->unkD == 1)
            {
                sub_8014EFC(0x16);
            }
            else if (data->unkD == 0)
            {
                sub_80152A8(0x16);
            }
            break;
        }
        data->unk8 = 6;
        break;
    case  6:
        if (gReceivedRemoteLinkPlayers != 0)
        {
            sub_8018838(TRUE);
            data->unk8 = 7;
            sub_801D484(data->unkC);
        }
        else if (gSpecialVar_Result == 5)
        {
            sub_8018838(TRUE);
            data->unk8 = 3;
        }
        break;
    case  7:
        sub_8018884(gText_Communicating);
        data->unk8 = 8;
        break;
    case  8:
        switch (sub_801D4A8(&data->unk0))
        {
        case 6:
            task_add_05_task_del_08FA224_when_no_RfuFunc();
            data->unkE = data->unk0;
            data->unk8 = 13;
            break;
        case 5:
            memcpy(data->unk10, sub_801D4F4(), 0x40);
            sub_801D4E4();
            break;
        case 3:
            data->unk8 = 10;
            break;
        case 2:
            data->unk8 = 9;
            break;
        case 4:
            data->unk8 = 11;
            StringCopy(gStringVar1, gLinkPlayers[0].name);
            break;
        }
        break;
    case  9:
        switch ((u32)sub_8018B08(&data->unk9, &data->unk0, FALSE, sub_801D4F4()))
        {
        case 0:
            sub_801D500(0);
            sub_801D4E4();
            data->unk8 = 7;
            break;
        case 1:
            sub_801D500(1);
            sub_801D4E4();
            data->unk8 = 7;
            break;
        case -1u:
            sub_801D500(1);
            sub_801D4E4();
            data->unk8 = 7;
            break;
        }
        break;
    case 10:
        if (mevent_0814257C(&data->unk9, sub_801D4F4()))
        {
            sub_801D4E4();
            data->unk8 = 7;
        }
        break;
    case 11:
        switch ((u32)sub_8018B08(&data->unk9, &data->unk0, FALSE, gText_ThrowAwayWonderCard))
        {
        case 0:
            if (sub_801B3F8() == TRUE)
            {
                data->unk8 = 12;
            }
            else
            {
                sub_801D500(0);
                sub_801D4E4();
                data->unk8 = 7;
            }
            break;
        case 1:
            sub_801D500(1);
            sub_801D4E4();
            data->unk8 = 7;
            break;
        case -1u:
            sub_801D500(1);
            sub_801D4E4();
            data->unk8 = 7;
            break;
        }
        break;
    case 12:
        switch ((u32)sub_8018B08(&data->unk9, &data->unk0, FALSE, gText_HaventReceivedCardsGift))
        {
        case 0:
            sub_801D500(0);
            sub_801D4E4();
            data->unk8 = 7;
            break;
        case 1:
            sub_801D500(1);
            sub_801D4E4();
            data->unk8 = 7;
            break;
        case -1u:
            sub_801D500(1);
            sub_801D4E4();
            data->unk8 = 7;
            break;
        }
        break;
    case 13:
        if (gReceivedRemoteLinkPlayers == 0)
        {
            sub_800E084();
            data->unk8 = 14;
        }
        break;
    case 14:
        if (sub_8018A1C(&data->unk9, gText_CommunicationCompleted))
        {
            if (data->unkD == 1)
            {
                StringCopy(gStringVar1, gLinkPlayers[0].name);
            }
            data->unk8 = 15;
        }
        break;
    case 15:
    {
        register bool32 flag asm("r1");
        r1 = mevent_message(&sp0, data->unkC, data->unkD, data->unkE);
        if (r1 == NULL)
        {
            r1 = data->unk10;
        }
        if (sp0)
        {
            flag = mevent_08142CE8(&data->unk9, r1, &data->unk0);
        }
        else
        {
            flag = mevent_0814257C(&data->unk9, r1);
        }
        if (flag)
        {
            if (data->unkE == 3)
            {
                if (data->unkD == 1)
                {
                    sub_801DB68(1);
                }
                else
                {
                    sub_801DB68(2);
                }
            }
            if (sp0 == 0)
            {
                data->unk8 = 0;
                sub_80186EC(0, 0);
            }
            else
            {
                data->unk8 = 17;
            }
        }
        break;
    }
    case 16:
        if (mevent_0814257C(&data->unk9, gText_CommunicationError))
        {
            data->unk8 = 0;
            sub_80186EC(0, 0);
        }
        break;
    case 17:
        if (mevent_save_game(&data->unk9))
        {
            data->unk8 = 18;
        }
        break;
    case 18:
        if (sub_8018DAC(&data->unk9, data->unkC))
        {
            data->unk8 = 20;
        }
        break;
    case 20:
        if (data->unkC == 0)
        {
            if (({gMain.newKeys & A_BUTTON;}))
            {
                data->unk8 = 21;
            }
            if (({gMain.newKeys & B_BUTTON;}))
            {
                data->unk8 = 27;
            }
        }
        else
        {
            switch (sub_801CCD0(gMain.newKeys))
            {
            case 0:
                sub_801CC38();
                data->unk8 = 21;
                break;
            case 1:
                data->unk8 = 27;
                break;
            }
        }
        break;
    case 21:
    {
        u32 result;
        if (data->unkC == 0)
        {
            if (sub_801B308())
            {
                result = sub_8018C4C(&data->unk9, &data->unk0, data->unkC, FALSE);
            }
            else
            {
                result = sub_8018C4C(&data->unk9, &data->unk0, data->unkC, TRUE);
            }
        }
        else
        {
            if (sub_801B128())
            {
                result = sub_8018C4C(&data->unk9, &data->unk0, data->unkC, FALSE);
            }
            else
            {
                result = sub_8018C4C(&data->unk9, &data->unk0, data->unkC, TRUE);
            }
        }
        switch (result)
        {
        case 0:
            data->unk8 = 28;
            break;
        case 1:
            data->unk8 = 29;
            break;
        case 2:
            data->unk8 = 22;
            break;
        case -2u:
            if (data->unkC == 1)
            {
                sub_801CC80();
            }
            data->unk8 = 20;
            break;
        }
        break;
    }
    case 22:
        switch (sub_8018E50(&data->unk9, &data->unk0, data->unkC))
        {
        case 0:
            if (data->unkC == 0 && sub_801B3F8() == TRUE)
            {
                data->unk8 = 23;
            }
            else
            {
                data->unk8 = 24;
            }
            break;
        case 1:
            data->unk8 = 21;
            break;
        case -1:
            data->unk8 = 21;
            break;
        }
        break;
    case 23:
        switch ((u32)sub_8018B08(&data->unk9, &data->unk0, TRUE, gText_HaventReceivedGiftOkayToDiscard))
        {
        case 0:
            data->unk8 = 24;
            break;
        case 1:
            data->unk8 = 21;
            break;
        case -1u:
            data->unk8 = 21;
            break;
        }
        break;
    case 24:
        if (sub_8018E20(data->unkC, 1))
        {
            sub_8018E08(data->unkC);
            data->unk8 = 25;
        }
        break;
    case 25:
        if (mevent_save_game(&data->unk9))
        {
            data->unk8 = 26;
        }
        break;
    case 26:
        if (mevent_message_was_thrown_away(&data->unk9, data->unkC))
        {
            data->unk8 = 0;
            sub_80186EC(0, 0);
        }
        break;
    case 27:
        if (sub_8018E20(data->unkC, 0))
        {
            data->unk8 = 0;
        }
        break;
    case 28:
        if (sub_8018E20(data->unkC, 1))
        {
            data->unk8 = 3;
        }
        break;
    case 29:
        if (sub_8018E20(data->unkC, 1))
        {
            switch (data->unkC)
            {
            case 0:
                sub_8014A00(21);
                break;
            case 1:
                sub_8014A00(22);
                break;
            }
            data->unkD = 1;
            data->unk8 = 30;
        }
        break;
    case 30:
        if (gReceivedRemoteLinkPlayers != 0)
        {
            sub_8018838(1);
            data->unk8 = 31;
        }
        else if (gSpecialVar_Result == 5)
        {
            sub_8018838(1);
            data->unk8 = 18;
        }
        break;
    case 31:
    {
        register u8 eos asm("r1");
        gStringVar1[0] = (eos = EOS);
        gStringVar2[0] = eos;
        gStringVar3[0] = eos;
    }
        if (data->unkC == 0)
        {
            sub_8018884(gText_SendingWonderCard);
            mevent_srv_new_wcard();
        }
        else
        {
            sub_8018884(gText_SendingWonderNews);
            mevent_srv_init_wnews();
        }
        data->unk8 = 32;
        break;
    case 32:
        if (sub_801D0C4(&data->unk0) == 3)
        {
            data->unkE = data->unk0;
            data->unk8 = 33;
        }
        break;
    case 33:
        task_add_05_task_del_08FA224_when_no_RfuFunc();
        StringCopy(gStringVar1, gLinkPlayers[1].name);
        data->unk8 = 34;
        break;
    case 34:
        if (gReceivedRemoteLinkPlayers == 0)
        {
            sub_800E084();
            data->unk8 = 35;
        }
        break;
    case 35:
        if (sub_8019174(&data->unk9, &data->unk0, data->unkD, data->unkE))
        {
            if (data->unkD == 1 && data->unkE == 3)
            {
                sub_801DB68(3);
                data->unk8 = 17;
            }
            else
            {
                data->unk8 = 0;
                sub_80186EC(0, 0);
            }
        }
        break;
    case 36:
        if (mevent_0814257C(&data->unk9, gText_CommunicationError))
        {
            data->unk8 = 0;
            sub_80186EC(0, 0);
        }
        break;
    case 37:
        CloseLink();
        Free(data->unk10);
        DestroyTask(taskId);
        SetMainCallback2(sub_80186A4);
        break;
    }
}
