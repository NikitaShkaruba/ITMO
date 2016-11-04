package itmo.dbs.models.repositories;

import itmo.dbs.models.Scenery;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.rest.core.annotation.RepositoryRestResource;

@RepositoryRestResource
public interface SceneryRepository extends CrudRepository<Scenery, Long> {}
