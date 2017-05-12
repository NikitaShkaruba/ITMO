package itmo.dbs.models.repositories;

import org.springframework.data.rest.core.annotation.RepositoryRestResource;
import org.springframework.data.mongodb.repository.MongoRepository;
import itmo.dbs.models.Species;

@RepositoryRestResource(collectionResourceRel = "species", path = "species")
public interface SpeciesRepository extends MongoRepository<Species, String> {}
