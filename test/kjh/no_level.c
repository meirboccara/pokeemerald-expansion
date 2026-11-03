// KJH (LV-4): no level shown; Bond in its place (src/kjh_bond.c).
#include "global.h"
#include "event_data.h"
#include "kjh_bond.h"
#include "string_util.h"
#include "test/test.h"

TEST("KJH: levels are hidden while the levels-free design is on")
{
    FlagSet(FLAG_KJH_LEVELLESS);
    EXPECT(KJH_HideLevels());
    FlagClear(FLAG_KJH_LEVELLESS);
    EXPECT(!KJH_HideLevels());
}

TEST("KJH: the Bond label replaces the level")
{
    u8 label[16];

    KJH_BufferBondLabel(label, KJH_BondToFriendship(12));
    EXPECT_EQ(StringCompare(label, COMPOUND_STRING("BOND 12")), 0);
    KJH_BufferBondLabel(label, 0);
    EXPECT_EQ(StringCompare(label, COMPOUND_STRING("BOND 1")), 0);
}
