package itmo.dbs.models.repositories;

import itmo.dbs.models.Texture;
import org.springframework.data.repository.CrudRepository;
import org.springframework.data.rest.core.annotation.RepositoryRestResource;

@RepositoryRestResource
public interface TexturesRepository extends CrudRepository<Texture, Long> {}
