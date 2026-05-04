#include "Hack.h"

VOID DrawBoneArmour()
{
    if (!V_BoneArmourEnabled || !GameReady() || !Me || V_MainMenuOpen || IsFullScreenPanelOpen() || IsPlayerInTown())
        return;

    const INT boneArmour = (INT)(GetUnitStat(Me, STAT_BONEARMOR) / 256);
    const INT boneArmourMax = (INT)(GetUnitStat(Me, STAT_MAXIMUMBONEARMOR) / 256);

    const INT screenCenterX = (*p_D2CLIENT_ScreenSizeX) / 2;
    const INT anchorX = screenCenterX + 80;
    const INT anchorY = 90;

    const INT barWidth = 80;
    const INT barHeight = 10;
    const INT barLeft = anchorX - (barWidth / 2);
    const INT barTop = anchorY - (barHeight / 2);
    const INT barRight = barLeft + barWidth;
    const INT barBottom = barTop + barHeight;

    DrawBox(barLeft, barTop, barRight, barBottom, COLOR_WHITE);

    INT fillWidth = 0;
    if (boneArmourMax > 0)
    {
        fillWidth = (boneArmour * (barWidth - 2)) / boneArmourMax;
        if (fillWidth < 0)
            fillWidth = 0;
        if (fillWidth > (barWidth - 2))
            fillWidth = barWidth - 2;
    }

    DWORD fillColor = COLOR_WHITE;
    if (boneArmourMax > 0)
    {
        const INT pct = (boneArmour * 100) / boneArmourMax;
        if (pct <= 25)
            fillColor = 10;
        else if (pct <= 50)
            fillColor = 12;
    }

    if (fillWidth > 0)
    {
        for (INT y = barTop + 1; y < barBottom; ++y)
        {
            D2GFX_DrawLine(barLeft + 1, y, barLeft + fillWidth, y, fillColor, -1);
        }
    }
}
