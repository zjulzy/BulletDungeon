# BulletDungeon

Developed with Unreal Engine 5

基于UE5的rougelike TPS闯关游戏
## 项目简介
## 游戏流程
## 项目结构
1. AbilitySysten/: GAS相关文件
2. Character/: 角色系统
3. Environment/: 关卡环境相关actor
4. Equipments/: 武器和可拾取物系统
5. Player/: player controller和player state
6. UI/: UI相关
## 项目实现
1. 技术实现
2. 游戏关卡设计
在游戏流程中玩家会经历一系列的关卡，每个关卡需要通过完成关卡目标才能通关  
关卡中的怪物通过预先放置的刷怪点随机间歇性刷新，在刷怪点附近巡逻，发现玩家后会向玩家移动攻击  
关卡中的道具通过预先放置的道具点间歇性刷新，玩家可以通过拾取道具点上的道具来获得道具
## 未来工作 
- [ ] 优化游戏AI
- [ ] 为关卡替换室内地图
- [x] 可视化关卡目标
- [ ] 实现可拾取血药
- [ ] 设计关卡通过后可以选择的buff
- [ ] 选择buff的可视化界面
- [ ] 背包可视化界面
- [ ] buff详情可视化界面
- [ ] 角色死亡相关处理
- [ ] 完善过关流程
