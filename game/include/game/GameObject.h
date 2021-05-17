#pragma once

#include <iostream>
#include <cassert>
#include <type_traits>
#include <array>
#include <vector>
#include <optional>
#include <functional>

#include <wglm/glm.hpp>
#include <misc/Misc.h>

#include "Signature.h"
/*#
everything_name: Everything
structure: sSoA
indirection_type: integers
type: Vector
size: 100
component[]: GamePosition
component[]: GraphicsTile
component[]: Brain
component[]: Nutrition
component[]: Locomotion
component[]: Possession
component[]: Vicinity
object_name: GameObject
#*/

struct ActionResult;
struct GameObject;
struct Possession;

enum GAMEOBJECT_COMPONENT;

template<class T>
struct Phantom {};

struct Executor
{
	template<class T>
	static void run();
};

template<class... Ts>
struct List
{
	static constexpr bool is_empty = true;
};

template<class Head, class... Tail>
struct List<Head, Tail...>
{
	static constexpr bool is_empty = false;
	using head = Head;
	using tail = List<Tail...>;
};

//template<class T, class... Ts>
//struct List
//{
//	static constexpr bool is_empty = sizeof...(Ts) == 0;
//	using head = T;
//	// using tail = List<Ts...>;
//	using tail = TryFill<sizeof...(Ts) != 0, List, Ts...>::type;
//};

template<class F, class L>
struct ForEach
{
	static void run() {
		if constexpr (!L::is_empty) {
			F::run<L::head>();
			ForEach<F, L::tail>::run();
		}
	};
};

template<class F, class L>
struct Fold
{

};

template<class T>
struct unwrap;

template<class R, class B, class... Args>
struct unwrap<R(B::*)(Args...) const>
{
	using std_function_type = std::function<R(Args...)>;
};

template<class T>
auto wrap2(T f) {
	using t = typename unwrap<decltype(&T::operator())>::std_function_type;
	return t(f);
}

template<class... Args>
static void run2(std::function<void(Args&...)> f) {

}

template<class T>
static void run(T f) {
	run2(wrap2(f));
}

class Action
{
public:
	std::vector<Signature<GAMEOBJECT_COMPONENT>> requirements{};
	std::vector<Signature<GAMEOBJECT_COMPONENT>> results{};

	//std::function<ActionResult(GameObject* obj)> runFunction;

	// obj should be the object which has access to the requirements in its possession
	//ActionResult run(GameObject* obj);
};

struct ActionResult
{
	bool success = false;

	std::vector<Possession> possessions{};
	std::vector<Action> actions{};
};

struct GamePosition
{
	glm::ivec2 pos;
};

struct GraphicsTile
{
	int32_t blockID;
};

struct Brain
{
	int32_t happiness = 0;
	int32_t energy = 0;

	std::optional<Action> currentAction;

	std::vector<Action> memory;

	Action const& findAction(std::vector<Signature<GameObject>> const& requirements);

	void merge(std::vector<Action>& other);
};

struct Possession
{
	//std::vector<UniqueReference<Object, Object>> inventory{};

	Possession() = default;

	DEFAULTMOVE(Possession);
	NOCOPY(Possession);
};

struct Vicinity
{
	//std::vector<WeakReference<Object, Object>> vicinity;
	//std::unique_ptr<GameObject> test;
};

struct Nutrition
{
	int32_t energy = 0;
};

struct Locomotion
{
	int32_t cooldown = 0;
	int32_t fitness = 60;

	std::optional<glm::ivec2> target;
};
//# forward
using SizeAlias = size_t;
struct Everything;
enum GAMEOBJECT_COMPONENT
{
	GAMEPOSITION,
	GRAPHICSTILE,
	BRAIN,
	NUTRITION,
	LOCOMOTION,
	POSSESSION,
	VICINITY,
	None,
	MAX
};
struct GameObjectProxy;
struct WeakGameObject;
struct UniqueGameObject;
//# end
//# declaration
struct Everything
{
	std::vector<GameObjectProxy> indirectionMap{ 100 };
	std::vector<GamePosition> gamepositions{ 100 };
	std::vector<GraphicsTile> graphicstiles{ 100 };
	std::vector<Brain> brains{ 100 };
	std::vector<Nutrition> nutritions{ 100 };
	std::vector<Locomotion> locomotions{ 100 };
	std::vector<Possession> possessions{ 100 };
	std::vector<Vicinity> vicinitys{ 100 };
	std::vector<Signature<GAMEOBJECT_COMPONENT>> signatures{ 100 };
	SizeAlias gamepositionlast{ 0 };
	SizeAlias graphicstilelast{ 0 };
	SizeAlias brainlast{ 0 };
	SizeAlias nutritionlast{ 0 };
	SizeAlias locomotionlast{ 0 };
	SizeAlias possessionlast{ 0 };
	SizeAlias vicinitylast{ 0 };
	size_t last{ 0 };
	template<class F>
	inline void run(F f);
	template<class... Args>
	inline void run2(std::function<void(Args...)> f);
	inline size_t takeFreeIndex();
	inline UniqueGameObject makeUnique();
	void remove(SizeAlias i);
	template<class T>
	inline std::vector<T>& gets();
	template<class T>
	inline T& get(SizeAlias i);
	inline GamePosition& gameposition(SizeAlias i);
	inline GraphicsTile& graphicstile(SizeAlias i);
	inline Brain& brain(SizeAlias i);
	inline Nutrition& nutrition(SizeAlias i);
	inline Locomotion& locomotion(SizeAlias i);
	inline Possession& possession(SizeAlias i);
	inline Vicinity& vicinity(SizeAlias i);
	inline bool hasgameposition(SizeAlias i);
	inline bool hasgraphicstile(SizeAlias i);
	inline bool hasbrain(SizeAlias i);
	inline bool hasnutrition(SizeAlias i);
	inline bool haslocomotion(SizeAlias i);
	inline bool haspossession(SizeAlias i);
	inline bool hasvicinity(SizeAlias i);
	inline void addgameposition(SizeAlias i);
	inline void addgraphicstile(SizeAlias i);
	inline void addbrain(SizeAlias i);
	inline void addnutrition(SizeAlias i);
	inline void addlocomotion(SizeAlias i);
	inline void addpossession(SizeAlias i);
	inline void addvicinity(SizeAlias i);
	inline Signature<GAMEOBJECT_COMPONENT>& signature(SizeAlias i);
};
struct GameObjectProxy
{
	Everything* proxy;
	size_t gameposition_;
	size_t graphicstile_;
	size_t brain_;
	size_t nutrition_;
	size_t locomotion_;
	size_t possession_;
	size_t vicinity_;
	inline GamePosition& gameposition();
	inline GraphicsTile& graphicstile();
	inline Brain& brain();
	inline Nutrition& nutrition();
	inline Locomotion& locomotion();
	inline Possession& possession();
	inline Vicinity& vicinity();
};
struct WeakGameObject
{
	size_t index{ 0 };
	Everything* proxy{ nullptr };
	inline bool hasgameposition();
	inline bool hasgraphicstile();
	inline bool hasbrain();
	inline bool hasnutrition();
	inline bool haslocomotion();
	inline bool haspossession();
	inline bool hasvicinity();
	inline void addgameposition();
	inline void addgraphicstile();
	inline void addbrain();
	inline void addnutrition();
	inline void addlocomotion();
	inline void addpossession();
	inline void addvicinity();
	inline GamePosition& gameposition();
	inline GraphicsTile& graphicstile();
	inline Brain& brain();
	inline Nutrition& nutrition();
	inline Locomotion& locomotion();
	inline Possession& possession();
	inline Vicinity& vicinity();
	inline Signature<GAMEOBJECT_COMPONENT>& signature();
	inline ~WeakGameObject();
	inline void clear();
	inline bool isNotNull() const;
	inline bool isNull() const;
};
struct UniqueGameObject
{
	size_t index{ 0 };
	Everything* proxy{ nullptr };
	inline bool hasgameposition();
	inline bool hasgraphicstile();
	inline bool hasbrain();
	inline bool hasnutrition();
	inline bool haslocomotion();
	inline bool haspossession();
	inline bool hasvicinity();
	inline void addgameposition();
	inline void addgraphicstile();
	inline void addbrain();
	inline void addnutrition();
	inline void addlocomotion();
	inline void addpossession();
	inline void addvicinity();
	inline GamePosition& gameposition();
	inline GraphicsTile& graphicstile();
	inline Brain& brain();
	inline Nutrition& nutrition();
	inline Locomotion& locomotion();
	inline Possession& possession();
	inline Vicinity& vicinity();
	inline Signature<GAMEOBJECT_COMPONENT>& signature();
	inline ~UniqueGameObject();
	inline void clear();
	inline bool isNotNull() const;
	inline bool isNull() const;
	UniqueGameObject() = default;
	NOCOPY(UniqueGameObject);
	UniqueGameObject(UniqueGameObject&& other);
	UniqueGameObject& operator=(UniqueGameObject&& other);
};
//# end
//# implementation
template<class F>
inline void Everything::run(F f) {
	this->run2(wrap2(f));
};
template<class... Args>
inline void Everything::run2(std::function<void(Args...)> f) {
	// TODO
};
inline size_t Everything::takeFreeIndex() {
	return last++;
};
inline UniqueGameObject Everything::makeUnique() {
	
};
inline GamePosition& Everything::gameposition(SizeAlias i) {
	return gamepositions[indirectionMap[i].gameposition_];
};
template<>
inline GamePosition& Everything::get<GamePosition>(SizeAlias i) {
	return gameposition(i);
};
template<>
inline std::vector<GamePosition>& Everything::gets<GamePosition>() {
	return gamepositions;
};
inline GraphicsTile& Everything::graphicstile(SizeAlias i) {
	return graphicstiles[indirectionMap[i].graphicstile_];
};
template<>
inline GraphicsTile& Everything::get<GraphicsTile>(SizeAlias i) {
	return graphicstile(i);
};
template<>
inline std::vector<GraphicsTile>& Everything::gets<GraphicsTile>() {
	return graphicstiles;
};
inline Brain& Everything::brain(SizeAlias i) {
	return brains[indirectionMap[i].brain_];
};
template<>
inline Brain& Everything::get<Brain>(SizeAlias i) {
	return brain(i);
};
template<>
inline std::vector<Brain>& Everything::gets<Brain>() {
	return brains;
};
inline Nutrition& Everything::nutrition(SizeAlias i) {
	return nutritions[indirectionMap[i].nutrition_];
};
template<>
inline Nutrition& Everything::get<Nutrition>(SizeAlias i) {
	return nutrition(i);
};
template<>
inline std::vector<Nutrition>& Everything::gets<Nutrition>() {
	return nutritions;
};
inline Locomotion& Everything::locomotion(SizeAlias i) {
	return locomotions[indirectionMap[i].locomotion_];
};
template<>
inline Locomotion& Everything::get<Locomotion>(SizeAlias i) {
	return locomotion(i);
};
template<>
inline std::vector<Locomotion>& Everything::gets<Locomotion>() {
	return locomotions;
};
inline Possession& Everything::possession(SizeAlias i) {
	return possessions[indirectionMap[i].possession_];
};
template<>
inline Possession& Everything::get<Possession>(SizeAlias i) {
	return possession(i);
};
template<>
inline std::vector<Possession>& Everything::gets<Possession>() {
	return possessions;
};
inline Vicinity& Everything::vicinity(SizeAlias i) {
	return vicinitys[indirectionMap[i].vicinity_];
};
template<>
inline Vicinity& Everything::get<Vicinity>(SizeAlias i) {
	return vicinity(i);
};
template<>
inline std::vector<Vicinity>& Everything::gets<Vicinity>() {
	return vicinitys;
};
inline bool Everything::hasgameposition(SizeAlias i) {
	return indirectionMap[i].gameposition_ != 0;
};
inline bool Everything::hasgraphicstile(SizeAlias i) {
	return indirectionMap[i].graphicstile_ != 0;
};
inline bool Everything::hasbrain(SizeAlias i) {
	return indirectionMap[i].brain_ != 0;
};
inline bool Everything::hasnutrition(SizeAlias i) {
	return indirectionMap[i].nutrition_ != 0;
};
inline bool Everything::haslocomotion(SizeAlias i) {
	return indirectionMap[i].locomotion_ != 0;
};
inline bool Everything::haspossession(SizeAlias i) {
	return indirectionMap[i].possession_ != 0;
};
inline bool Everything::hasvicinity(SizeAlias i) {
	return indirectionMap[i].vicinity_ != 0;
};
inline void Everything::addgameposition(SizeAlias i) {
	signature(i).set(GAMEPOSITION);
};
inline void Everything::addgraphicstile(SizeAlias i) {
	signature(i).set(GRAPHICSTILE);
};
inline void Everything::addbrain(SizeAlias i) {
	signature(i).set(BRAIN);
};
inline void Everything::addnutrition(SizeAlias i) {
	signature(i).set(NUTRITION);
};
inline void Everything::addlocomotion(SizeAlias i) {
	signature(i).set(LOCOMOTION);
};
inline void Everything::addpossession(SizeAlias i) {
	signature(i).set(POSSESSION);
};
inline void Everything::addvicinity(SizeAlias i) {
	signature(i).set(VICINITY);
};
inline Signature<GAMEOBJECT_COMPONENT>& Everything::signature(SizeAlias i) {
	return signatures[i];
};
inline GamePosition& GameObjectProxy::gameposition() {
	return proxy->gamepositions[gameposition_];
};
inline GraphicsTile& GameObjectProxy::graphicstile() {
	return proxy->graphicstiles[graphicstile_];
};
inline Brain& GameObjectProxy::brain() {
	return proxy->brains[brain_];
};
inline Nutrition& GameObjectProxy::nutrition() {
	return proxy->nutritions[nutrition_];
};
inline Locomotion& GameObjectProxy::locomotion() {
	return proxy->locomotions[locomotion_];
};
inline Possession& GameObjectProxy::possession() {
	return proxy->possessions[possession_];
};
inline Vicinity& GameObjectProxy::vicinity() {
	return proxy->vicinitys[vicinity_];
};
inline bool WeakGameObject::hasgameposition() {
	return proxy->hasgameposition(index);
};
inline bool WeakGameObject::hasgraphicstile() {
	return proxy->hasgraphicstile(index);
};
inline bool WeakGameObject::hasbrain() {
	return proxy->hasbrain(index);
};
inline bool WeakGameObject::hasnutrition() {
	return proxy->hasnutrition(index);
};
inline bool WeakGameObject::haslocomotion() {
	return proxy->haslocomotion(index);
};
inline bool WeakGameObject::haspossession() {
	return proxy->haspossession(index);
};
inline bool WeakGameObject::hasvicinity() {
	return proxy->hasvicinity(index);
};
inline void WeakGameObject::addgameposition() {
	proxy->addgameposition(index);
};
inline void WeakGameObject::addgraphicstile() {
	proxy->addgraphicstile(index);
};
inline void WeakGameObject::addbrain() {
	proxy->addbrain(index);
};
inline void WeakGameObject::addnutrition() {
	proxy->addnutrition(index);
};
inline void WeakGameObject::addlocomotion() {
	proxy->addlocomotion(index);
};
inline void WeakGameObject::addpossession() {
	proxy->addpossession(index);
};
inline void WeakGameObject::addvicinity() {
	proxy->addvicinity(index);
};
inline GamePosition& WeakGameObject::gameposition() {
	return proxy->gameposition(index);
};
inline GraphicsTile& WeakGameObject::graphicstile() {
	return proxy->graphicstile(index);
};
inline Brain& WeakGameObject::brain() {
	return proxy->brain(index);
};
inline Nutrition& WeakGameObject::nutrition() {
	return proxy->nutrition(index);
};
inline Locomotion& WeakGameObject::locomotion() {
	return proxy->locomotion(index);
};
inline Possession& WeakGameObject::possession() {
	return proxy->possession(index);
};
inline Vicinity& WeakGameObject::vicinity() {
	return proxy->vicinity(index);
};
inline Signature<GAMEOBJECT_COMPONENT>& WeakGameObject::signature() {
	return proxy->signature(index);
};
inline WeakGameObject::~WeakGameObject() {
	clear();
};
inline void WeakGameObject::clear() {
	proxy->remove(index);
	index = 0;
	proxy = nullptr;
};
inline bool WeakGameObject::isNotNull() const {
	return index != 0;
};
inline bool WeakGameObject::isNull() const {
	return index == 0;
};
inline bool UniqueGameObject::hasgameposition() {
	return proxy->hasgameposition(index);
};
inline bool UniqueGameObject::hasgraphicstile() {
	return proxy->hasgraphicstile(index);
};
inline bool UniqueGameObject::hasbrain() {
	return proxy->hasbrain(index);
};
inline bool UniqueGameObject::hasnutrition() {
	return proxy->hasnutrition(index);
};
inline bool UniqueGameObject::haslocomotion() {
	return proxy->haslocomotion(index);
};
inline bool UniqueGameObject::haspossession() {
	return proxy->haspossession(index);
};
inline bool UniqueGameObject::hasvicinity() {
	return proxy->hasvicinity(index);
};
inline void UniqueGameObject::addgameposition() {
	proxy->addgameposition(index);
};
inline void UniqueGameObject::addgraphicstile() {
	proxy->addgraphicstile(index);
};
inline void UniqueGameObject::addbrain() {
	proxy->addbrain(index);
};
inline void UniqueGameObject::addnutrition() {
	proxy->addnutrition(index);
};
inline void UniqueGameObject::addlocomotion() {
	proxy->addlocomotion(index);
};
inline void UniqueGameObject::addpossession() {
	proxy->addpossession(index);
};
inline void UniqueGameObject::addvicinity() {
	proxy->addvicinity(index);
};
inline GamePosition& UniqueGameObject::gameposition() {
	return proxy->gameposition(index);
};
inline GraphicsTile& UniqueGameObject::graphicstile() {
	return proxy->graphicstile(index);
};
inline Brain& UniqueGameObject::brain() {
	return proxy->brain(index);
};
inline Nutrition& UniqueGameObject::nutrition() {
	return proxy->nutrition(index);
};
inline Locomotion& UniqueGameObject::locomotion() {
	return proxy->locomotion(index);
};
inline Possession& UniqueGameObject::possession() {
	return proxy->possession(index);
};
inline Vicinity& UniqueGameObject::vicinity() {
	return proxy->vicinity(index);
};
inline Signature<GAMEOBJECT_COMPONENT>& UniqueGameObject::signature() {
	return proxy->signature(index);
};
inline UniqueGameObject::~UniqueGameObject() {
	clear();
};
inline void UniqueGameObject::clear() {
	proxy->remove(index);
	index = 0;
	proxy = nullptr;
};
inline bool UniqueGameObject::isNotNull() const {
	return index != 0;
};
inline bool UniqueGameObject::isNull() const {
	return index == 0;
};
//# end