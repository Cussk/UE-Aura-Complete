# Top-Down RPG (Unreal Engine 5, Gameplay Ability System)

This repository contains an in-progress top-down RPG built in Unreal Engine 5. The project showcases a scalable and expandable code base, architected with AAA-quality standards, using both **C++** and **Blueprints** in balance.  

It serves as a strong foundation for creating serious games that include interconnected systems such as attributes, abilities, enemies, multiplayer support, and more. The project leverages Unreal’s **Gameplay Ability System (GAS)** to implement complex RPG mechanics while keeping the code modular, maintainable, and easy to extend.

---

## ✨ Features

- **Top-Down RPG Framework** with player character, enemies, spells, and progression systems  
- **Gameplay Ability System (GAS)** implementation:
  - Custom attributes, attribute sets, and replication  
  - Primary Attributes: Strength, Intelligence, Resilience, Vigor  
  - Secondary Attributes: Armor, Armor Penetration, Block Chance, Crit Chance, Crit Damage, etc.  
  - Vital Attributes: Health and Mana  
  - Gameplay Effects & Tags for scalable combat and status effects  

- **Combat & Damage System**
  - Multiple damage types and resistances  
  - Critical hits, blocks, debuffs (burning, stun, knockback, etc.)  
  - Floating combat text with critical/block variations  

- **Spells & Abilities**
  - Offensive spells (FireBolt, Electrocute, Arcane Shards, FireBlast, etc.)  
  - Passive spells that remain active when equipped  
  - Ability costs, cooldowns, and keybinding customization  

- **Progression Systems**
  - Experience and Level-Up system  
  - Attribute and Spell Points gained on level up  
  - Upgradeable Attributes and Spell Trees  

- **AI & Enemies**
  - Multiple enemy archetypes (Ranger, Warrior, Elementalist, etc.)  
  - Enemy AI using Behavior Trees and Environment Query System (EQS)  
  - Enemies can cast spells and summon allies  

- **User Interface**
  - Modular UI built with MVC/MVVM principles  
  - Attribute and Spell menus with upgrade trees  
  - HUD with spell slots, cooldowns, XP, and level tracking  

- **Additional Systems**
  - Save/Load progress  
  - Dungeon environments with modular assets  
  - Camera fade-out of obstructing geometry  
  - Multiplayer-ready architecture  

---

## 🛠️ Tech Highlights

- **Unreal Engine 5.6+** as the development platform  
- **Gameplay Ability System (GAS)**:
  - Deep integration of core GAS classes (Abilities, Effects, Tags, Attribute Sets)  
  - Custom extensions for flexible replication and multiplayer support  
- **C++ & Blueprints in balance**:
  - Roughly 50/50 split between systems implemented in C++ and in Blueprints  
  - Clear separation of responsibilities: performance-critical systems in C++, gameplay iteration in Blueprints  
- **SOLID coding principles** applied throughout for maintainability and scalability  
- **Advanced Unreal concepts**, including:  
  - Custom Gameplay Effect Contexts  
  - Custom Ability and Async Tasks  
  - Blueprint Function Libraries  
  - Asset Manager integration for handling large-scale content  
  - Selective use of Singletons where appropriate  
  - Net Serialization and custom struct operations for multiplayer robustness  
- **Scalable architecture** designed to handle complex interconnected systems (attributes, abilities, UI, AI, and multiplayer) without sacrificing clarity or maintainability  
