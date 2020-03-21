#include "AsteroidsSystem.h"
#include "GameCtrlSystem.h"


void AsteroidsSystem::update() {

	int totalAsteroids = 0;
	for (auto& e : mngr_->getGroupEntities(ecs::_grp_Asteroid)) {
		if (!e->isActive()) { return; };

		totalAsteroids++;
		Transform* tr = e->getComponent<Transform>(ecs::Transform);
		if (tr != nullptr) {

			Vector2D newPos = { tr->position_.getX() + tr->velocity_.getX(),
				tr->position_.getY() + tr->velocity_.getY() };
			tr->position_.set(newPos);
			//Si sale de la pantalla
			if (tr->position_.getX() < 0) tr->position_.set({ (double)game_->getWindowWidth(), tr->position_.getY() });			//Izquierda
			else if (tr->position_.getX() > game_->getWindowWidth()) tr->position_.set({ 0, tr->position_.getY() });			//Derecha

			if (tr->position_.getY() < 0) tr->position_.set({ tr->position_.getX(), (double)game_->getWindowHeight() });		//Arriba
			else if (tr->position_.getY() > game_->getWindowHeight()) tr->position_.set({ tr->position_.getX(), 0 });			//Abajo
		}

	}
	 
	/*if (GETCMP2(mngr_->getHandler(ecs::_hdlr_GameState), GameState)->getCurrSTate() == STATE::STARTED && totalAsteroids == 0) {
		mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->onAsteroidsExtenction();
	}*/
}