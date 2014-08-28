LandConfig		(暂缺)
SceneConfig		场景配置表
ZoneConfig		区域配置表

SkillConfig		技能配置表
EffectConfig		判定配置表
BuffConfig		光环配置表
ItemConfig		道具配置表
BagConfig		包裹属性配置表
EquipConfig		装备属性配置表
DeputyConfig		副职配置表
DeputySkillConfig	副职技能配置表
GuildConfig		工会配置表
GuildRankConfig		工会会阶配置表
GuildRankRightsConfig	工会会阶权限配置表
MajorMissionConfig	主线任务配置表
MinorMissionConfig	随机任务配置表
CollectionConfig	矿石、尸体配置表
 

FigureConfig		身材配置表
JobConfig		职业配置表
MonsterConfig		怪物配置表

PropertyConfig		生物属性配置表

AvatarConfig		(暂缺)
BlockConfig		障碍配置表

GuildRankConfig		(工会默认会阶)


sceneconfig说明
ID号，场景ID
区域名称，该区域的名称
场景类型，该场景属于home或是城镇或是其他区域类型
资源名称，该scene的资源名称
根节点名称，场景剪裁的关键点参数
所在大陆ID，所在世界大陆ID，用于定位home位置
区域长宽，可行动范围长宽高
诞生坐标，玩家在home和墓地的诞生坐标
传送门数组，传送门位置、资源等信息，一个场景需要四个传送门位置
NPC数组，场景NPC的位置和ID
障碍总数量，场景出现障碍的最大数量
障碍ID数组，场景可出现的障碍ID
采集物同
障碍&采集点坐标数组，障碍与采集点可出现的坐标位置，平均每屏12个
怪物节点数组，怪物在scene中所处的位置和数量
boss、特殊障碍同
