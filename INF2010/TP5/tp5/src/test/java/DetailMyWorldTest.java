import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;
import java.util.stream.Collectors;

import DetailMyWorld.DetailMyWorld;

public class DetailMyWorldTest {

    private DetailMyWorldIO readIO(String problemNumber) throws FileNotFoundException {
        Scanner scanner = new Scanner(new File("src/test/resources/DetailMyWorld/inputs/input" + problemNumber + ".txt"));
        DetailMyWorldIO interview = new DetailMyWorldIO();

        interview.isBreadthFirstSearch = scanner.nextLine().equals("1");

        while (scanner.hasNextLine()) {
            String listString = scanner.nextLine();
            List<Integer> row = Arrays
                    .stream(listString.split(" +"))
                    .map(Integer::parseInt)
                    .collect(Collectors.toList());

            interview.world.add(new ArrayList<>(row));
        }

        scanner = new Scanner(new File("src/test/resources/DetailMyWorld/outputs/output" + problemNumber + ".txt"));
        while (scanner.hasNextLine()) {
            String listString = scanner.nextLine();
            Set<Integer> countries = Arrays
                    .stream(listString.split(" +"))
                    .map(Integer::parseInt)
                    .collect(Collectors.toSet());

            interview.expected.add(countries);
        }

        return interview;
    }

    private void verifyAnswers(List<Set<Integer>> expected, List<Set<Integer>> actual) {
        assertNotNull(actual);
        assertEquals(expected.size(), actual.size());

        Iterator<Set<Integer>> actualIt = actual.iterator();
        Iterator<Set<Integer>> expectedIt = expected.iterator();

        for (int i = 0; i < actual.size(); ++i)
            assertArrayEquals(expectedIt.next().toArray(), actualIt.next().toArray());
    }

    @Test
    void input00() throws FileNotFoundException {
        DetailMyWorldIO interview = readIO("00");
        List<Set<Integer>> continents = DetailMyWorld.findContinents(interview.world, interview.isBreadthFirstSearch);
        verifyAnswers(interview.expected, continents);
    }

    @Test
    void input01() throws FileNotFoundException {
        DetailMyWorldIO interview = readIO("01");
        List<Set<Integer>> continents = DetailMyWorld.findContinents(interview.world, interview.isBreadthFirstSearch);
        verifyAnswers(interview.expected, continents);
    }

    @Test
    void input02() throws FileNotFoundException {
        DetailMyWorldIO interview = readIO("02");
        List<Set<Integer>> continents = DetailMyWorld.findContinents(interview.world, interview.isBreadthFirstSearch);
        verifyAnswers(interview.expected, continents);
    }

    @Test
    void input03() throws FileNotFoundException {
        DetailMyWorldIO interview = readIO("03");
        List<Set<Integer>> continents = DetailMyWorld.findContinents(interview.world, interview.isBreadthFirstSearch);
        verifyAnswers(interview.expected, continents);
    }

    @Test
    void input04() throws FileNotFoundException {
        DetailMyWorldIO interview = readIO("04");
        List<Set<Integer>> continents = DetailMyWorld.findContinents(interview.world, interview.isBreadthFirstSearch);
        verifyAnswers(interview.expected, continents);
    }

    @Test
    void input05() throws FileNotFoundException {
        DetailMyWorldIO interview = readIO("05");
        List<Set<Integer>> continents = DetailMyWorld.findContinents(interview.world, interview.isBreadthFirstSearch);
        verifyAnswers(interview.expected, continents);
    }

    @Test
    void input06() throws FileNotFoundException {
        DetailMyWorldIO interview = readIO("06");
        List<Set<Integer>> continents = DetailMyWorld.findContinents(interview.world, interview.isBreadthFirstSearch);
        verifyAnswers(interview.expected, continents);
    }

    @Test
    void input07() throws FileNotFoundException {
        DetailMyWorldIO interview = readIO("07");
        List<Set<Integer>> continents = DetailMyWorld.findContinents(interview.world, interview.isBreadthFirstSearch);
        verifyAnswers(interview.expected, continents);
    }

    @Test
    void input08() throws FileNotFoundException {
        DetailMyWorldIO interview = readIO("08");
        List<Set<Integer>> continents = DetailMyWorld.findContinents(interview.world, interview.isBreadthFirstSearch);
        verifyAnswers(interview.expected, continents);
    }

    @Test
    void input09() throws FileNotFoundException {
        DetailMyWorldIO interview = readIO("09");
        List<Set<Integer>> continents = DetailMyWorld.findContinents(interview.world, interview.isBreadthFirstSearch);
        verifyAnswers(interview.expected, continents);
    }

    static private class DetailMyWorldIO {
        ArrayList<ArrayList<Integer>> world;
        Boolean isBreadthFirstSearch;
        ArrayList<Set<Integer>> expected;

        DetailMyWorldIO() {
            world = new ArrayList<>();
            expected = new ArrayList<>();
        }
    }
}
