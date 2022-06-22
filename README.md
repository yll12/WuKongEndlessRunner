<!-- ABOUT THE PROJECT -->
## About The Project
<a href="https://youtu.be/Ph1tOzIDEV8">Youtube preview</a>

Features I implemented:
* Endless, randomised, 2D platform, based on a set of predefined levels. See <a href="https://github.com/yll12/WuKongEndlessRunner/blob/master/Source/WuKongEndlessRunner/Private/LevelSpawner.cpp">LevelSpawner.cpp</a>
* Extracted logic into Actor components to be used by any actors:
  * HealthAndTakeDamage
  * Death
  * EnemyWeaponEffect
  * AttackCombo
  * HitReact
  * Superarmor (Enable certain period where the actor cannot be interrupted)
* Health HUD
* Wukong's cloud summon/unsummon, particle effects depending on velocity
* Wukong double jump (using backflip for the double jump animation)
* End game screen
* Extracted some common AI task/decator in preparation for reusing AI logic
  *  IsPlayerActorDead
  *  AttackTarget
  *  RotateToFaceTarget

Assets I used:
* Unreal Engine Hour of Code
* Paragon Wukong
* Paragon Minions
* Sound Phenomenon Fantasy Orchestra

### Built With

* Unreal Engine 4
* Visual Studio 2022 (C++)

## Contact me

[![LinkedIn][linkedin-shield]][linkedin-url]

<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[contributors-shield]: https://img.shields.io/github/contributors/othneildrew/Best-README-Template.svg?style=for-the-badge
[contributors-url]: https://github.com/othneildrew/Best-README-Template/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/othneildrew/Best-README-Template.svg?style=for-the-badge
[forks-url]: https://github.com/othneildrew/Best-README-Template/network/members
[stars-shield]: https://img.shields.io/github/stars/othneildrew/Best-README-Template.svg?style=for-the-badge
[stars-url]: https://github.com/othneildrew/Best-README-Template/stargazers
[issues-shield]: https://img.shields.io/github/issues/othneildrew/Best-README-Template.svg?style=for-the-badge
[issues-url]: https://github.com/othneildrew/Best-README-Template/issues
[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/othneildrew/Best-README-Template/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/yong-li-l-54178ba6
