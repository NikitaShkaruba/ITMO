package itmo.dbs.models.repositories;

import org.springframework.data.rest.core.annotation.RepositoryRestResource;
import org.springframework.data.mongodb.repository.MongoRepository;
import itmo.dbs.models.Pet;

@RepositoryRestResource
public interface PetsRepository extends MongoRepository<Pet, String> {}
