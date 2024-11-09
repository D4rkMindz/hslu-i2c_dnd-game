#include <stdio.h>
#include "map.h"
#include <stdlib.h>

// Define the number of rooms
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

// Helper function to set descriptions for a room
void setRoomDescriptions(Room *room, const char *description, const char *lookAroundText)
{
    room->description = description;
    room->lookAroundText = lookAroundText;
}

// Initialize each room with specific exits, features, monsters, and descriptions
Room **initializeMap()
{
    // Allocate and initialize each room
    for (int i = 0; i < TOTAL_ROOMS; i++)
    {
        rooms[i] = (Room *)malloc(sizeof(Room));
        rooms[i]->hasMonster = false;
        rooms[i]->hasSecretPassage = false;
        rooms[i]->monsterDefeated = false;
        rooms[i]->secretPassageRevealed = false;
        setRoomExits(rooms[i], NONE, NONE, NONE, NONE); // Initialize exits to NONE
        rooms[i]->description = "";
        rooms[i]->lookAroundText = "";
    }

    // Room 0: Tutorial Room
    setRoomExits(rooms[0], 2, NONE, NONE, NONE);
    setRoomDescriptions(rooms[0],
                        "The solid stone doors slam shut behind you with a resounding finality, cutting off any chance of escape. The air here is thick with dust and decay, and only one path lies open, leading north. The walls are etched with faint, weathered symbols, perhaps once bearing warnings or tales, but now too worn to decipher.",
                        "As you run your hands over the cold stone walls, you feel the etchings' grooves but can make nothing of them. It’s as though time itself tried to erase the secrets that this place holds. The silence is oppressive, and a chill hangs in the air, as though this place has not seen the light of day—or any living being—for centuries.");

    // Room 2: First Room with secret passage and monster
    setRoomExits(rooms[2], 5, 3, NONE, 1);
    rooms[2]->hasSecretPassage = true;
    rooms[2]->hasMonster = true;
    setRoomDescriptions(rooms[2],
                        "A dim glow from a small, ancient water fountain at the center of the room reflects off the walls, casting eerie shadows. The fountain bubbles weakly, and a thick, viscous slime lurks nearby, its translucent form pulsing in the darkness.",
                        "The fountain is carved with intricate patterns of skulls and skeletal hands reaching upwards, as if in silent screams. There’s a faint inscription near the base: “Life can be drained, yet linger on.” The slime pulsates, giving the impression that it’s somehow alive—maybe even aware. A subtle energy seems to emanate from the fountain, as though it has absorbed something over the ages.");

    // Room 1: Two visible exits
    setRoomExits(rooms[1], 4, 2, NONE, NONE);
    setRoomDescriptions(rooms[1],
                        "A treasure chest sits in the center, covered in dust, its metal bindings rusted but still sturdy. The walls here bear strange etchings, more preserved than those at the entrance.",
                        "The etchings tell fragmented stories. You see depictions of people bound to tables, figures cloaked in shadow hovering over them with strange tools, and symbols of life twisted into unnatural forms. Words in an old dialect speak of “undying pain” and “the eternity of flesh.” It seems that this place might have been a workshop or laboratory. The chest, though old, appears untouched by recent visitors.");

    // Room 3: Two visible exits
    setRoomExits(rooms[3], 6, NONE, NONE, 2);
    setRoomDescriptions(rooms[3],
                        "A treasure chest lies here, set against the wall beneath faded etchings. Shadows dance around the room, hinting at stories long forgotten.",
                        "The etchings here reveal more details: a figure cloaked in royal attire standing over a congregation of faceless beings. The text nearby speaks of “experiments in vitality” and a “sacrifice for eternal life.” It’s unsettling—this King might have seen his subjects as nothing more than tools for his twisted experiments. The chest’s rusty lock groans as though protesting your touch.");

    // Room 5: Four exits, one hidden to Room 4
    setRoomExits(rooms[5], 8, 6, 2, 4);
    rooms[4]->hasSecretPassage = true;
    setRoomDescriptions(rooms[5],
                        "A treasure chest lies open, its contents strangely preserved, while the walls bear unusually clear etchings, each line sharp and deeply carved.",
                        "These etchings are clearer than in other rooms, depicting complex anatomical diagrams and symbols of unnatural regeneration. Detailed texts speak of “binding the soul” and “the art of restoring flesh.” This must have been a place where the King recorded his most prized knowledge. The chest holds brittle parchments and strange vials, hints of experiments both grisly and arcane.");

    // Room 4: Visible and hidden exit, with a monster
    setRoomExits(rooms[4], 7, NONE, 1, NONE);
    rooms[4]->hasMonster = true;
    setRoomDescriptions(rooms[4],
                        "An animated skeleton stands guard, its eyes dimly glowing, as if aware of your presence. The walls here bear etchings similar to those in previous rooms, though the meanings seem darker, more threatening.",
                        "The walls depict prisoners, gaunt and hollow-eyed, shackled to the stone. Inscribed nearby: “Only the strongest of spirit may endure beyond death.” This place feels different, charged, as if imbued with something dark and ancient. The skeleton, though seemingly mindless, stands watch as if it’s guarding something far more valuable than mere treasure.");

    // Room 6: Visible and hidden exit, with a monster
    setRoomExits(rooms[6], 9, NONE, 3, NONE);
    rooms[6]->hasSecretPassage = true;
    rooms[6]->hasMonster = true;
    setRoomDescriptions(rooms[6],
                        "A animated skeleton shuffles in the room, and its hollow gaze turns toward you. The walls are covered with disturbing illustrations and runes that radiate an eerie energy.",
                        "The illustrations show men and women splayed open, their innards twisted into grotesque patterns, with the King standing nearby, watching. The runes warn, “Those who watch shall also guard,” and the skeleton’s restless movements give credence to these words. It seems the King's servants were bound in death to protect his secrets.");

    // Room 7: Two exits
    setRoomExits(rooms[7], NONE, 8, 4, NONE);
    setRoomDescriptions(rooms[7],
                        "A treasure chest rests here, the dust around it undisturbed. Clear and precise etchings cover the walls, as if painstakingly preserved.",
                        "These etchings are more advanced—drawings of limbs, organs, and skulls, with strange symbols marking areas of “extended vitality” and “forced revival.” The texts speak of “living beyond one’s mortal span” and “imprisonment of the self.” This room exudes a sense of dread, as though what’s written here was never meant to be read by anyone still alive.");

    // Room 9: Two exits
    setRoomExits(rooms[9], NONE, NONE, 6, 8);
    setRoomDescriptions(rooms[9],
                        "Another chest lies here, and the etchings on the walls are incredibly detailed, showing clear intent.",
                        "Here, you find diagrams of a massive ritual, one that required sacrifices by the dozens. The texts describe how “those bound to eternal servitude shall guard the throne,” hinting that many were sacrificed in this very room. You sense that whatever lies ahead is not merely a place of death, but a prison for something far worse.");

    // Room 8: Visible and hidden exit, with a monster
    setRoomExits(rooms[8], 10, 9, NONE, 7);
    rooms[8]->hasSecretPassage = true;
    rooms[8]->hasMonster = true;
    setRoomDescriptions(rooms[8],
                        "A treasure chest lies here, alongside deeply informative etchings. The air feels heavier, the silence more oppressive.",
                        "The etchings here describe a ritual of “binding and entrapment,” with drawings of a cloaked figure trapped within stone walls, hands clawing in vain for release. Words like “eternity,” “torment,” and “undying king” are scratched deeply into the wall, almost angrily. You feel a sense of foreboding, as if something terrible awaits you just beyond.");

    // Boss Room (Room 10) with a monster
    setRoomExits(rooms[10], NONE, NONE, 8, NONE);
    rooms[10]->hasMonster = true;
    setRoomDescriptions(rooms[10],
                        "The door slams shut behind you, trapping you in a grand chamber. At the center is an altar, and behind it sits an unnaturally large figure slumped on a throne, crowned with gold. It grins at you with an expression that chills you to the core.",
                        "The creature’s form is grotesque, with limbs that seem too long, joints that bend the wrong way, and a smile that stretches impossibly wide. The crown gleams with an untouched radiance, and the walls are covered with scratch marks, some fresh, others ancient, as if countless things—or perhaps this thing itself—had tried to escape. There are no inscriptions here, no history preserved, only this grotesque being’s maddening grin and the sense that you’re not alone in this room—far from it.");

    return rooms;
}

// Function to retrieve a room by its number
Room *getRoom(int roomNumber)
{
    if (roomNumber >= 0 && roomNumber < TOTAL_ROOMS)
    {
        return rooms[roomNumber];
    }
    return NULL; // Return NULL if room number is out of bounds
}