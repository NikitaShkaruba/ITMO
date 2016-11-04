package itmo.dbs.models.repositories;

import org.springframework.data.repository.CrudRepository;
import itmo.dbs.models.Food;
import org.springframework.data.rest.core.annotation.RepositoryRestResource;

@RepositoryRestResource(collectionResourceRel = "food", path = "food")
public interface FoodRepository extends CrudRepository<Food, Long> {}
