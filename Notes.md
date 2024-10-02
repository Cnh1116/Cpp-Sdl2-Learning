--- Class Organization / Functionality ---

The window class has a update method. Maybe ESC quits, ` opens debug menu
Sprite Class
Item Class
Player Class
Enemy Class
Math Class


--- Goals ---

1. Debug Screen -> Maybe main and debug screen are apart of the game class
2. Draw a sprite
3. If SDL_Event == 'D', sprite move right
4. Change Background
5. Primary and secondary fire

--- My Game Ideas ---

1. Make the game _9_ tiles wide. ITems can spawn on the "bridge". _3_ tiles wide. Bridge shifts collumns over time.
2. Having a primary fire to straight forward, secondary fire to pick up items on the "bridge"
3. A full body shield that breaks when hit. Has X amoount of cooldown. Make this act like a parry, very low amount of time active and then a quick cooldown to use it again.
  3.a. Shield should record how much damage attack was: normalize 1 damage to MAX_IN_GAME damage, and multiply this percentage to a max frequency sound to play when absorbing damage. higher pitch for absorbing more damage.

--- Item Ideas ---

- Ruby Radio - Fire Damage 🔥
- Saphire ... Ice Damage ❄️
- Emerald ... Poison / Nature ? 🌱
- Diamond ... Arcane / 🔮

- Iron - Take less damage
- Gold - Speed ⬆️
- Platinum - DPS up ?

- Glass Toucan - Damage or crit?
- Wooden Frog ⬇️ Lower "parry / shield" CDR
- Plastic
