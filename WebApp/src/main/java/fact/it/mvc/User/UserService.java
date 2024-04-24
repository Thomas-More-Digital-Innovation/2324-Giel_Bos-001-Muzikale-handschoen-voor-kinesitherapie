package fact.it.mvc.User;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import java.util.List;

@Service
public class UserService {
    @Autowired
    private final UserRepository userRepository;

    public UserService(UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    public List<User> getAllUsers() {
        return userRepository.findAll();
    }

    public User getUserById(int userID) {
        return userRepository.findById(userID).orElse(null);
    }

    public User createUser(User user) {
        return userRepository.save(user);
    }

    public User updateUser(int userID, User updatedUser) {
        if (!userRepository.existsById(userID)) {
            return null;
        }
        updatedUser.setUserID(userID); // Ensure the ID is set correctly
        return userRepository.save(updatedUser);
    }

    public void deleteUser(int userID) {
        userRepository.deleteById(userID);
    }
}
