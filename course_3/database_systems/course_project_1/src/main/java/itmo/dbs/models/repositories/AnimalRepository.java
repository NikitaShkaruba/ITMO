package itmo.dbs.models.repositories;

import itmo.dbs.models.Animal;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.rest.core.annotation.RepositoryRestResource;

@RepositoryRestResource
public interface AnimalRepository extends CrudRepository<Animal, Long> {}
