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
        "The solid stone doors slam shut behind you with a resounding finality, cutting off any chance of escape.\n",
        "The air here is thick with dust and decay, and only one path lies open, leading north.\n",
        "The walls are etched with faint, weathered symbols, perhaps once bearing warnings or tales, but now too worn to decipher.\n"};
    const char *look0[] = {
        "As you run your hands over the cold stone walls, you feel the etchings grooves but can make nothing of them.\n",
        "It is as though time itself tried to erase the secrets that this place holds.\n",
        "The silence is oppressive, and a chill hangs in the air, as though this place has not seen the light of day or any living being for centuries.\n"};
    setRoomDescriptions(rooms[0], desc0, 3, look0, 3);
    setRoomExits(rooms[0], 2, NONE, NONE, NONE);

    // Room 1: The Etched Hall
    const char *desc1[] = {
        "A treasure chest sits in the center, covered in dust, its metal bindings rusted but still sturdy.\n",
        "The walls here bear strange etchings, more preserved than those at the entrance.\n"};
    const char *look1[] = {
        "The etchings tell fragmented stories.\n",
        "You see depictions of people bound to tables, figures cloaked in shadow hovering over them with strange tools, and symbols of life twisted into unnatural forms.\n",
        "Words in an old dialect speak of undying pain and the eternity of flesh.\n",
        "It seems that this place might have been a workshop or laboratory.\n",
        "The chest, though old, appears untouched by recent visitors.\n"};
    setRoomDescriptions(rooms[1], desc1, 2, look1, 5);
    setRoomExits(rooms[1], 4, 2, NONE, NONE);

    // Room 2: Fountain Room
    const char *desc2[] = {
        "A dim glow from a small, ancient water fountain at the center of the room reflects off the walls, casting eerie shadows.\n",
        "The fountain bubbles weakly, and a thick, viscous slime lurks nearby, its translucent form pulsing in the darkness.\n"};
    const char *look2[] = {
        "The fountain is carved with intricate patterns of skulls and skeletal hands reaching upwards, as if in silent screams.\n",
        "There is a faint inscription near the base: Life can be drained, yet linger on.\n",
        "The slime pulsates, giving the impression that it is somehow alive, maybe even aware.\n",
        "A subtle energy seems to emanate from the fountain, as though it has absorbed something over the ages.\n"};
    setRoomDescriptions(rooms[2], desc2, 2, look2, 4);
    setRoomExits(rooms[2], 5, 3, NONE, 1);
    rooms[2]->hasMonster = true;
    rooms[2]->hasSecretPassage = true;

    // Room 3: Storeroom
    const char *desc3[] = {
        "A treasure chest lies here, set against the wall beneath faded etchings.\n",
        "Shadows dance around the room, hinting at stories long forgotten.\n"};
    const char *look3[] = {
        "The etchings here reveal more details: a figure cloaked in royal attire standing over a congregation of faceless beings.\n",
        "The text nearby speaks of experiments in vitality and a sacrifice for eternal life.\n",
        "It is unsettling; this King might have seen his subjects as nothing more than tools for his twisted experiments.\n",
        "The chest's rusty lock groans as though protesting your touch.\n"};
    setRoomDescriptions(rooms[3], desc3, 2, look3, 4);
    setRoomExits(rooms[3], 6, NONE, NONE, 2);

    // Room 4: Skeleton Guardian
    const char *desc4[] = {
        "An animated skeleton stands guard, its eyes dimly glowing, as if aware of your presence.\n",
        "The walls here bear etchings similar to those in previous rooms, though the meanings seem darker, more threatening.\n"};
    const char *look4[] = {
        "The walls depict prisoners, gaunt and hollow-eyed, shackled to the stone.\n",
        "Inscribed nearby: Only the strongest of spirit may endure beyond death.\n",
        "This place feels different, charged, as if imbued with something dark and ancient.\n",
        "The skeleton, though seemingly mindless, stands watch as if it is guarding something far more valuable than mere treasure.\n"};
    setRoomDescriptions(rooms[4], desc4, 2, look4, 4);
    setRoomExits(rooms[4], 7, NONE, 1, NONE);
    rooms[4]->hasMonster = true;

    // Room 5: Knowledge Vault
    const char *desc5[] = {
        "A treasure chest lies open, its contents strangely preserved, while the walls bear unusually clear etchings, each line sharp and deeply carved.\n"};
    const char *look5[] = {
        "These etchings are clearer than in other rooms, depicting complex anatomical diagrams and symbols of unnatural regeneration.\n",
        "Detailed texts speak of binding the soul and the art of restoring flesh.\n",
        "This must have been a place where the King recorded his most prized knowledge.\n",
        "The chest holds brittle parchments and strange vials, hints of experiments both grisly and arcane.\n"};
    setRoomDescriptions(rooms[5], desc5, 1, look5, 4);
    setRoomExits(rooms[5], 8, 6, 2, 4);

    // Room 6: The Watcher's Tomb
    const char *desc6[] = {
        "An animated skeleton shuffles in the room, and its hollow gaze turns toward you.\n",
        "The walls are covered with disturbing illustrations and runes that radiate an eerie energy.\n"};
    const char *look6[] = {
        "The illustrations show men and women splayed open, their innards twisted into grotesque patterns, with the King standing nearby, watching.\n",
        "The runes warn, Those who watch shall also guard, and the skeletons restless movements give credence to these words.\n",
        "It seems the King's servants were bound in death to protect his secrets.\n"};
    setRoomDescriptions(rooms[6], desc6, 2, look6, 3);
    setRoomExits(rooms[6], 9, NONE, 3, NONE);
    rooms[6]->hasMonster = true;
    rooms[6]->hasSecretPassage = true;

    // Room 7: Repository of Dark Knowledge
    const char *desc7[] = {
        "A treasure chest rests here, the dust around it undisturbed.\n",
        "Clear and precise etchings cover the walls, as if painstakingly preserved.\n"};
    const char *look7[] = {
        "These etchings are more advanced—drawings of limbs, organs, and skulls, with strange symbols marking areas of extended vitality and forced revival.\n",
        "The texts speak of living beyond one's mortal span and imprisonment of the self.\n",
        "This room exudes a sense of dread, as though what is written here was never meant to be read by anyone still alive.\n"};
    setRoomDescriptions(rooms[7], desc7, 2, look7, 3);
    setRoomExits(rooms[7], NONE, 8, 4, NONE);

    // Room 8: The Final Gate
    const char *desc8[] = {
        "A treasure chest lies here, alongside deeply informative etchings.\n",
        "The air feels heavier, the silence more oppressive.\n"};
    const char *look8[] = {
        "The etchings here describe a ritual of binding and entrapment, with drawings of a cloaked figure trapped within stone walls, hands clawing in vain for release.\n",
        "Words like eternity, torment, and undying king are scratched deeply into the wall, almost angrily.\n",
        "You feel a sense of foreboding, as if something terrible awaits you just beyond.\n"};
    setRoomDescriptions(rooms[8], desc8, 2, look8, 3);
    setRoomExits(rooms[8], 10, 9, NONE, 7);
    rooms[8]->hasMonster = true;
    rooms[8]->hasSecretPassage = true;

    // Room 9: Forsaken Crypt
    const char *desc9[] = {
        "Another chest lies here, and the etchings on the walls are incredibly detailed, showing clear intent.\n"};
    const char *look9[] = {
        "Here, you find diagrams of a massive ritual, one that required sacrifices by the dozens.\n",
        "The texts describe how those bound to eternal servitude shall guard the throne, hinting that many were sacrificed in this very room.\n",
        "You sense that whatever lies ahead is not merely a place of death, but a prison for something far worse.\n"};
    setRoomDescriptions(rooms[9], desc9, 1, look9, 3);
    setRoomExits(rooms[9], NONE, NONE, 6, 8);

    // Room 10: Throne of the Forgotten King
    const char *desc10[] = {
        "The door slams shut behind you, trapping you in a grand chamber.\n",
        "At the center is an altar, and behind it sits an unnaturally large figure slumped on a throne, crowned with gold.\n",
        "It grins at you with an expression that chills you to the core.\n"};
    const char *look10[] = {
        "The creature's form is grotesque, with limbs that seem too long, joints that bend the wrong way, and a smile that stretches impossibly wide.\n",
        "The crown gleams with an untouched radiance, and the walls are covered with scratch marks, some fresh, others ancient, as if countless things—or perhaps this thing itself—had tried to escape.\n",
        "There are no inscriptions here, no history preserved, only this grotesque being's maddening grin and the sense that you are not alone in this room—far from it.\n"};
    setRoomDescriptions(rooms[10], desc10, 3, look10, 3);
    setRoomExits(rooms[10], NONE, NONE, 8, NONE);
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
