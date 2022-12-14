#include "ComponentArray_Old.h"

template <typename T>
void ComponentArray_Old<T>::InsertData(Entity entity, T component)
{
	check(EntityToIndexMap.find(entity) != EntityToIndexMap.end());

	size_t newIndex = Size;
	EntityToIndexMap[entity] = newIndex;
	IndexToEntityMap[newIndex] = entity;
	ComponentArray[newIndex] = component;
	++Size;
}

template <typename T>
void ComponentArray_Old<T>::RemoveData(Entity entity)
{
	check(EntityToIndexMap.find(entity) != EntityToIndexMap.end());

	size_t indexOfRemovedEntity = EntityToIndexMap[entity];
	size_t indexOfLastElement = Size - 1;
	ComponentArray[indexOfRemovedEntity] = ComponentArray[indexOfLastElement];

	Entity entityOfLastElement = IndexToEntityMap[indexOfLastElement];
	EntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
	IndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

	EntityToIndexMap.erase(entity);
	IndexToEntityMap.erase(indexOfLastElement);

	--Size;
}

template <typename T>
T &ComponentArray_Old<T>::GetData(Entity entity)
{
	check(EntityToIndexMap.find(entity) != EntityToIndexMap.end());

	return ComponentArray[EntityToIndexMap[entity]];
}

template <typename T>
void ComponentArray_Old<T>::EntityDestroyed(Entity entity)
{
	check(EntityToIndexMap.find(entity) != EntityToIndexMap.end());

	RemoveData(entity);
}
