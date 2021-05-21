#include "GameState.h"

#include <render/infos/RenderInfo.h>

#include <mem/Locator.h>
#include <render/textures/BlockIDTextures.h>

#include <cstdlib>

#include <misc/Timer.h>

namespace game
{
	void GameState::addRenderInfo(render::RenderInfo& renderInfo) {
		Locator<misc::Timer>::ref().newTiming("new2");
		this->everything2.run([&](game::MatchS<GamePosition, GraphicsTile>& e) {
			renderInfo.tileRenderInfo.addBlitInfo(
				glm::vec4(e.get<GamePosition>().pos, 1, 1),
				0,
				e.get<GraphicsTile>().blockID
			);
			});

		Locator<misc::Timer>::ref().endTiming("new2");

	}

	void GameState::runTick() {
		SignatureAlias conciousSignature;
		conciousSignature.set(GAMEOBJECT_COMPONENT::BRAIN);
		conciousSignature.set(GAMEOBJECT_COMPONENT::POSSESSION);
		conciousSignature.set(GAMEOBJECT_COMPONENT::VICINITY);

		SignatureAlias foodSignature;
		foodSignature.set(GAMEOBJECT_COMPONENT::NUTRITION);

		SignatureAlias friendlySignature;
		friendlySignature.set(GAMEOBJECT_COMPONENT::BRAIN);

		SignatureAlias brainSignature;
		brainSignature.set(GAMEOBJECT_COMPONENT::BRAIN);

		SignatureAlias locomotionSignature;
		locomotionSignature.set(GAMEOBJECT_COMPONENT::LOCOMOTION);
		locomotionSignature.set(GAMEOBJECT_COMPONENT::GAMEPOSITION);

		Concept foodConcept;

		foodConcept.essences.push_back({ 10.0f, foodSignature });
		foodConcept.essences.push_back({ -10.0f, friendlySignature });

		this->everything2.run([](MatchS<Locomotion, GamePosition>& e) {
			if (e.get<Locomotion>().cooldown != 0) {
				e.get<Locomotion>().cooldown--;
			}
			else {
				e.get<Locomotion>().cooldown = e.get<Locomotion>().fitness;
				e.get<GamePosition>().pos += glm::ivec2((rand() % 3) - 1, (rand() % 3) - 1);
			}
			});

		this->tick++;
	}

	struct Void {};

	GameState::GameState() {
		{
			{
				//auto p = this->everything->makeWeak();
				//p.addbrain();
				//p.addpossession();
				//p.addvicinity();
				//p.addgraphicstile();
				//p.addlocomotion();
				//p.addgameposition();

				//p.gameposition().pos = { 5 , 5 };

				//p.graphicstile().blockID = Locator<render::BlockIDTextures>::ref().getBlockTextureID("gnome.dds");

				//p.locomotion().fitness = 10;
			}
			{
				auto p = this->everything2.make();
				p.add<Brain>();
				p.add<Vicinity>();
				p.add<GraphicsTile>();
				p.add<Locomotion>();
				p.add<GamePosition>();

				p.get<GamePosition>().pos = { 5, 5 };

				p.get<GraphicsTile>().blockID = Locator<render::BlockIDTextures>::ref().getBlockTextureID("gnome.dds");

				p.get<Locomotion>().fitness = 10;
			}

			//Action recallFood;
			//recallFood.requirements = {};
			//SignatureAlias foodSignature;
			//foodSignature.set(GAMEOBJECT_COMPONENT::NUTRITION).set(GAMEOBJECT_COMPONENT::GAMEPOSITION);
			//recallFood.results = { foodSignature };
			////recallFood.runFunction = [](Object* obj) -> ActionResult
			////{
			////	ActionResult result{};

			////	return result;
			////};
		}


		{
			//auto ref = this->refMan.makeRef<Object>();
			//auto ptr = ref.get();

			//glm::ivec2 pos = { 14, 14 };

			//ptr->signature.set(GAMEOBJECT_COMPONENT::GAMEPOSITION);
			//ptr->gamePosition().pos = pos;
			//this->world[14][14] = ref;

			//ptr->signature.set(GAMEOBJECT_COMPONENT::GRAPHICSTILE);
			//ptr->graphicsTile().blockID = Locator<render::BlockIDTextures>::ref().getBlockTextureID("food.dds");
		}


		for (size_t i = 0; i < WORLD_SIZE; i++) {
			//for (size_t j = 0; j < 30; j++) {
			{
				size_t j = 0;
				auto p2 = this->everything2.make();
				p2.add<GamePosition>();
				p2.add<GraphicsTile>();

				p2.get<GamePosition>().pos = glm::ivec2(i, j);
				p2.get<GraphicsTile>().blockID = Locator<render::BlockIDTextures>::ref().getBlockTextureID("weird_ground.dds");


				//this->world[i][j] = ref;
			}
		}

		for (size_t i = 0; i < WORLD_SIZE; i++) {
			//for (size_t j = 0; j < 30; j++) {
			{
				int j = WORLD_SIZE - 1;
				auto p2 = this->everything2.make();
				p2.add<GamePosition>();
				p2.add<GraphicsTile>();

				p2.get<GamePosition>().pos = glm::ivec2(i, j);
				p2.get<GraphicsTile>().blockID = Locator<render::BlockIDTextures>::ref().getBlockTextureID("weird_ground.dds");
			}
		}

		//for (size_t i = 0; i < 30; i++) {
		{
			size_t i = 0;
			for (size_t j = 0; j < WORLD_SIZE; j++) {
				auto p2 = this->everything2.make();
				p2.add<GamePosition>();
				p2.add<GraphicsTile>();

				p2.get<GamePosition>().pos = glm::ivec2(i, j);
				p2.get<GraphicsTile>().blockID = Locator<render::BlockIDTextures>::ref().getBlockTextureID("weird_ground.dds");
			}
		}

		//for (size_t i = 0; i < 30; i++) {
		{
			int i = WORLD_SIZE - 1;
			for (size_t j = 0; j < WORLD_SIZE; j++) {
				auto p2 = this->everything2.make();
				p2.add<GamePosition>();
				p2.add<GraphicsTile>();

				p2.get<GamePosition>().pos = glm::ivec2(i, j);
				p2.get<GraphicsTile>().blockID = Locator<render::BlockIDTextures>::ref().getBlockTextureID("weird_ground.dds");
			}
		}
	}

	float Concept::value(SignatureAlias const& signature) {
		float result = 0.0f;

		for (auto const& essence : this->essences) {
			if (signature.contains(essence.signature)) {

				result += essence.value;
			}
		}

		return result;
	}
}
