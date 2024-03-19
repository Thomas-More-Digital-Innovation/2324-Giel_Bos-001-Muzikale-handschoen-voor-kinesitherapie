package fact.it.mvc.RewardMusicList;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import java.util.List;
import java.util.Optional;

@Service
public class RewardMusicListService {
    @Autowired
    private final RewardMusicListRepository rewardMusicListRepository;

    public RewardMusicListService(RewardMusicListRepository rewardMusicListRepository) {
        this.rewardMusicListRepository = rewardMusicListRepository;
    }

    public List<RewardMusicList> getAllRewardMusicLists() {
        return rewardMusicListRepository.findAll();
    }

    public Optional<RewardMusicList> getRewardMusicListById(int id) {
        return rewardMusicListRepository.findById(id);
    }

    public RewardMusicList saveRewardMusicList(RewardMusicList rewardMusicList) {
        return rewardMusicListRepository.save(rewardMusicList);
    }

    public void deleteRewardMusicListById(int id) {
        rewardMusicListRepository.deleteById(id);
    }

    // You can add more service methods as per your application requirements
}
