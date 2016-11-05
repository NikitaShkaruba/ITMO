package itmo.dbs.models.repositories;

import itmo.dbs.models.Pet;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.rest.core.annotation.RepositoryRestResource;

@RepositoryRestResource
public interface PetsRepository extends CrudRepository<Pet, Long> {}
