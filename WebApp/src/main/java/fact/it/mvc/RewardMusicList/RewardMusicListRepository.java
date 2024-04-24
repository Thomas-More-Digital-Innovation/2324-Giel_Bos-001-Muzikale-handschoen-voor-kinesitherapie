package fact.it.mvc.RewardMusicList;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import java.util.List;

@Repository
public interface RewardMusicListRepository extends JpaRepository<RewardMusicList, Integer> {
    // You can add custom query methods here if needed
    List<RewardMusicList> findByRwMID(int rwMID);
}