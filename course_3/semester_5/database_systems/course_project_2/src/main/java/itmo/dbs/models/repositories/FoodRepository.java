package itmo.dbs.models.repositories;

import org.springframework.data.rest.core.annotation.RepositoryRestResource;
import org.springframework.data.mongodb.repository.MongoRepository;
import itmo.dbs.models.Food;

@RepositoryRestResource(collectionResourceRel = "food", path = "food")
public interface FoodRepository extends MongoRepository<Food, String> {}
