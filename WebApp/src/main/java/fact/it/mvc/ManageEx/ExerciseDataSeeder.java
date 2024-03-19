package fact.it.mvc.ManageEx;

import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Component;

import java.util.List;

@Component
public class ExerciseDataSeeder implements CommandLineRunner {

    private final ExerciseRepository exerciseRepository;

    public ExerciseDataSeeder(ExerciseRepository exerciseRepository) {
        this.exerciseRepository = exerciseRepository;
    }

    @Override
    public void run(String... args) throws Exception {
        // Check if data exists
        if (exerciseRepository.count() == 0) {
            // Add dummy data only if no data exists
            Exercise exercise1 = new Exercise();
            exercise1.setExString("dummyString1");
            exercise1.setName("Exercise 1");
            exercise1.setPicture("/img/ex0.jpg");
            exercise1.setDescription("Description 1");

            Exercise exercise2 = new Exercise();
            exercise2.setExString("dummyString2");
            exercise2.setName("Exercise 2");
            exercise2.setPicture("/img/ex1.jpg");
            exercise2.setDescription("Description 2");

            Exercise exercise3 = new Exercise();
            exercise3.setExString("dummyString3");
            exercise3.setName("Exercise 3");
            exercise3.setPicture("/img/ex2.jpg");
            exercise3.setDescription("Description 3");

            exerciseRepository.saveAll(List.of(exercise1, exercise2, exercise3));
        }
    }
}