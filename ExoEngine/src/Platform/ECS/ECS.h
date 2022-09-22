#pragma once

#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"
#include "Types.h"
#include "ECSprecompiled.h"

namespace BaseEngine
{
	class ECS
	{
	public:
		void Init()
		{
			mComponentManager = std::make_unique<ComponentManager>();
			mEntityManager = std::make_unique<EntityManager>();
			mSystemManager = std::make_unique<SystemManager>();
		}


		// Entity methods
		EntityID CreateEntity()
		{
			return mEntityManager->CreateEntity();
		}

		void DestroyEntity(EntityID entity)
		{
			mEntityManager->DestroyEntity(entity);

			mComponentManager->EntityDestroyed(entity);

			mSystemManager->EntityDestroyed(entity);
		}


		// Component methods
		template<typename T>
		void RegisterComponent()
		{
			mComponentManager->RegisterComponent<T>();
		}

		template<typename T>
		void AddComponent(EntityID entity, T component)
		{
			mComponentManager->AddComponent<T>(entity, component);

			auto signature = mEntityManager->GetSignature(entity);
			signature.set(mComponentManager->GetComponentType<T>(), true);
			mEntityManager->SetSignature(entity, signature);

			mSystemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		void RemoveComponent(EntityID entity)
		{
			mComponentManager->RemoveComponent<T>(entity);

			auto signature = mEntityManager->GetSignature(entity);
			signature.set(mComponentManager->GetComponentType<T>(), false);
			mEntityManager->SetSignature(entity, signature);

			mSystemManager->EntitySignatureChanged(entity, signature);
		}

		template<typename T>
		T& GetComponent(EntityID entity)
		{
			return mComponentManager->GetComponent<T>(entity);
		}

		template<typename T>
		ComponentTypeID GetComponentType()
		{
			return mComponentManager->GetComponentType<T>();
		}


		// System methods
		template<typename T>
		std::shared_ptr<T> RegisterSystem()
		{
			return mSystemManager->RegisterSystem<T>();
		}

		template<typename T>
		void SetSystemSignature(SignatureID signature)
		{
			mSystemManager->SetSignature<T>(signature);
		}

	private:
		std::unique_ptr<ComponentManager> mComponentManager;
		std::unique_ptr<EntityManager> mEntityManager;
		std::unique_ptr<SystemManager> mSystemManager;
	};
}
