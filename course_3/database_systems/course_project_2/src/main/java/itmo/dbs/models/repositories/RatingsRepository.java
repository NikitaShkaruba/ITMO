package itmo.dbs.models.repositories;

import org.springframework.data.rest.core.annotation.RepositoryRestResource;
import org.springframework.data.mongodb.repository.MongoRepository;
import itmo.dbs.models.Rating;

@RepositoryRestResource
public interface RatingsRepository extends MongoRepository<Rating, String> {}
