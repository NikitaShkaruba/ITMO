package itmo.dbs.models.repositories;

import itmo.dbs.models.Rating;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.rest.core.annotation.RepositoryRestResource;

@RepositoryRestResource
public interface RatingsRepository extends CrudRepository<Rating, Long> {}
