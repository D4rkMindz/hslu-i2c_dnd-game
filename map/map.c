#include <stdio.h>
#include "map.h"
#include <stdlib.h>

#define TOTAL_ROOMS 11

// Static array of Room pointers
static Room *rooms[TOTAL_ROOMS];

// Helper function to set room exits
void setRoomExits(Room *room, int north, int east, int south, int west)
{
    room->exits[NORTH] = north;
    room->exits[EAST] = east;
    room->exits[SOUTH] = south;
    room->exits[WEST] = west;
}

// Helper function to set descriptions and look-around texts for a room
void setRoomDescriptions(Room *room, const char *description[], int descLineCount, const char *lookAroundText[], int lookLineCount)
{
    for (int i = 0; i < descLineCount; i++)
    {
        room->description[i] = description[i];
    }
    room->descriptionLineCount = descLineCount;

    for (int i = 0; i < lookLineCount; i++)
    {
        room->lookAroundText[i] = lookAroundText[i];
    }
    room->lookAroundLineCount = lookLineCount;
}

// Initialize each room with specific exits, features, monsters, and descriptions
Room **initializeMap()
{
    for (int i = 0; i < TOTAL_ROOMS; i++)
    {
        rooms[i] = (Room *)malloc(sizeof(Room));
        rooms[i]->hasMonster = false;
        rooms[i]->hasSecretPassage = false;
        rooms[i]->monsterDefeated = false;
        rooms[i]->secretPassageRevealed = false;
        setRoomExits(rooms[i], NONE, NONE, NONE, NONE);
    }

    // Room 0: Entrance
    const char *desc0[] = {
        "\r.... A heavy door slams shut behind you with a resounding finality, cutting off any chance of escape.\r",
        "You came to this Temple searching for gold and riches, as told in the legends, but a seed of doubt and fear has been planted in your heart.\r",
        "The air here is thick with dust and decay, and only one path lies open, leading north.\r"};
    const char *look0[] = {
        "As you run your hands over the cold stone walls, you find that the walls are etched with faint, weathered symbols, perhaps once bearing warnings or tales, but now too worn to decipher.\r",
        "It is as though time itself tried to erase the secrets that this place holds.\r",
        "You look back towards the entrance you came through and push on the door with all your strength. It doesn't even budge.\r"};
    setRoomDescriptions(rooms[0], desc0, 3, look0, 3);
    setRoomExits(rooms[0], 2, NONE, NONE, NONE);

    // Room 1: The Etched Hall
    const char *desc1[] = {
        "A treasure chest sits in the center, covered in dust, its metal bindings rusted but still sturdy.\r",
        "The walls here bear strange etchings, more preserved than those at the entrance.\r"};
    const char *look1[] = {
        "The etchings tell fragmented stories.\r",
        "You see depictions of people bound to tables, figures cloaked in shadow hovering over them with strange tools, and symbols of life twisted into unnatural forms.\r",
        "Words in an old dialect speak of undying pain and the eternity of flesh.\r",
        "You open the chest to find a pair of extremely old-fashioned goggles.\r",
        "Upon putting them on, you realise that they make you look extremely lame. You chuckle and continue on.\r"};
    setRoomDescriptions(rooms[1], desc1, 2, look1, 5);
    setRoomExits(rooms[1], 4, 2, NONE, NONE);

    // Room 2: Fountain Room
    const char *desc2[] = {
        "A dim glow from a small, ancient water fountain at the center of the room reflects off the walls, casting eerie shadows.\r",
        "The fountain bubbles weakly, and you see traces of a Slime on the floor. It probably lurks nearby, its translucent form pulsing in the darkness.\r"};
    const char *look2[] = {
        "The fountain is carved with intricate patterns of skulls and skeletal hands reaching upwards.\r",
        "There is a faint inscription near the base: Life can be drained, yet linger on.\r",
        "You begin to question the reason this Temple's King was forgotten.\r",
        "Reality is setting in. You are stuck in the Temple unless you find a second way out.\r"};
    setRoomDescriptions(rooms[2], desc2, 2, look2, 4);
    setRoomExits(rooms[2], NONE, 3, NONE, 1);
    rooms[2]->hasMonster = true;
    rooms[2]->hasSecretPassage = true;

    // Room 3: Storeroom
    const char *desc3[] = {
        "A Chest lies here, set against the wall beneath faded etchings.\r",
        "Shadows dance around the room, hinting at stories long forgotten.\r"};
    const char *look3[] = {
        "The etchings here reveal more details: a figure cloaked in royal attire standing over a congregation of faceless beings.\r",
        "You feel as though you are being watched.\r",
        "It is unsettling and you have a fleeting thought: this King might not have been forgotten, but removed from History.\r",
        "The chest's rusty lock groans as though protesting your touch.\r"};
    setRoomDescriptions(rooms[3], desc3, 2, look3, 4);
    setRoomExits(rooms[3], 6, NONE, NONE, 2);

    // Room 4: Skeleton Guardian
    const char *desc4[] = {
        "An animated skeleton stands guard, its eyes dimly glowing, as if aware of your presence.\r",
        "A stone slab sits in the middle of the room covered in grime and dust.\r"};
    const char *look4[] = {
        "The walls depict prisoners, gaunt and hollow-eyed, shackled to the stone.\r",
        "You see scrolls mentioning experiments in vitality and a sacrifice for eternal life.\r",
        "This place feels different, charged, as if imbued with something dark and ancient.\r",
        "The skeleton, though seemingly mindless, stands watch as if it is guarding something far more valuable than mere treasure.\r"};
    setRoomDescriptions(rooms[4], desc4, 2, look4, 4);
    setRoomExits(rooms[4], 7, NONE, 1, NONE);
    rooms[4]->hasMonster = true;
    rooms[4]->hasSecretPassage = true;

    // Room 5: Knowledge Vault
    const char *desc5[] = {
        "A table overflowing with ancient scrolls and dusty items is in the middle of this room.",
        "The walls bear unusually clear etchings, each line sharp and deeply carved.\r"};
    const char *look5[] = {
        "These etchings depict complex anatomical diagrams and symbols of unnatural regeneration.\r",
        "This must have been a place where the King recorded his darkest experiments.\r",
        "The chest holds brittle parchments and strange vials, hints of experiments both grisly and arcane.\r",
        "Detailed texts speak of binding the soul and the art of restoring flesh.\r"};
    setRoomDescriptions(rooms[5], desc5, 1, look5, 4);
    setRoomExits(rooms[5], 8, 6, 2, 4);

    // Room 6: The Watcher's Tomb
    const char *desc6[] = {
        "An animated skeleton shuffles in the room, and its hollow gaze turns toward you.\r",
        "There are open books scattered around the room with pages of illustrations and runes that radiate an eerie energy.\r"};
    const char *look6[] = {
        "The illustrations show men and women splayed open, their innards twisted into grotesque patterns, with the Healers standing nearby, watching.\r",
        "The runes warn, Those who watch shall also guard, and the skeletons restless movements give credence to these words.\r",
        "It seems the King's servants were bound in death to protect his secrets.\r"};
    setRoomDescriptions(rooms[6], desc6, 2, look6, 3);
    setRoomExits(rooms[6], 9, NONE, 3, NONE);
    rooms[6]->hasMonster = true;
    rooms[6]->hasSecretPassage = true;

    // Room 7: Repository of Dark Knowledge
    const char *desc7[] = {
        "A treasure chest rests here, the dust around it undisturbed.\r",
        "Clear and precise etchings cover the walls, as if painstakingly preserved.\r"};
    const char *look7[] = {
        "These etchings are more advanced. You see drawings of limbs, organs, and skulls, with strange symbols marking areas of extended vitality and forced revival.\r",
        "The texts speak of living beyond one's mortal span and imprisonment of the self.\r",
        "This room exudes a sense of dread, as though what is written here was never meant to be read by anyone still alive.\r"};
    setRoomDescriptions(rooms[7], desc7, 2, look7, 3);
    setRoomExits(rooms[7], NONE, 8, 4, NONE);

    // Room 8: The Final Gate
    const char *desc8[] = {
        "A large heavy door lies on the northward wall. It gleams in the low light and you notice it is encrusted with many jewels.\r",
        "The air feels heavier, the silence more oppressive. You instinctively understand that this is your final destination.\r"};
    const char *look8[] = {
        "You find diagrams of a massive ritual, one that required sacrifices by the dozens.\r",
        "The texts describe how those bound to eternal servitude shall guard the throne, hinting that many were sacrificed in this very room.\r",
        "You sense that whatever lies ahead is not merely a place of death, but a prison for something far worse.\r"};
    setRoomDescriptions(rooms[8], desc8, 2, look8, 3);
    setRoomExits(rooms[8], 10, 9, NONE, 7);

    // Room 9: Forsaken Crypt
    const char *desc9[] = {
        "Another chest lies here, and the etchings on the walls are incredibly detailed.\r"};
    const char *look9[] = {
        "The etchings here describe a ritual of binding and entrapment, with drawings of a cloaked figure trapped within stone walls, hands clawing in vain for release.\r",
        "Words are scratched deeply into the wall, almost angrily. You can only make out: Eternity, Torment, and Undying King\r",
        "You feel a sense of foreboding, as if something terrible awaits you just beyond.\r"};
    setRoomDescriptions(rooms[9], desc9, 1, look9, 3);
    setRoomExits(rooms[9], NONE, NONE, 6, 8);

    // Room 10: Throne of the Forgotten King
    const char *desc10[] = {
        "The door slams shut behind you, trapping you in a grand chamber.\r",
        "At the center is an altar, and behind it sits an unnaturally large figure slumped on a throne, a golden crown sits atop it's head.\r",
        "It grins at you with an expression that chills you to the core.\r"};
    const char *look10[] = {
        "The creature's form is grotesque, with limbs that seem too long, joints that bend the wrong way, and a smile that stretches impossibly wide.\r",
        "The crown gleams with an untouched radiance, and the walls are covered with scratch marks. Many seem to have tried to escape this room through any means available.\r",
        "There are no inscriptions here, no history preserved, only this grotesque being's maddening grin and the sense that there is no way out of this fight.\r"};
    setRoomDescriptions(rooms[10], desc10, 3, look10, 3);
    setRoomExits(rooms[10], NONE, NONE, NONE, NONE);
    rooms[10]->hasMonster = true;

    return rooms;
}

// Function to retrieve a room by its number
Room *getRoom(int roomNumber)
{
    if (roomNumber >= 0 && roomNumber < TOTAL_ROOMS)
    {
        return rooms[roomNumber];
    }
    return NULL;
}
