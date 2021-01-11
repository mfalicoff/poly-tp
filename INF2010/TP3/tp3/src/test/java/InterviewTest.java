import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class InterviewTest {
    @Test
    void squareShape() {
        Interview<Integer> interview = new Interview<>(new Integer[][] {
                {1,2,5},
                {29,67,98},
                {100,245,900}
        });

        assertTrue(interview.contains(1));
        assertTrue(interview.contains(67));
        assertTrue(interview.contains(900));

        assertFalse(interview.contains(35));
    }

    @Test
    void rectangleShape() {
        Interview<Integer> interview = new Interview<>(new Integer[][] {
                {1,2,5,18},
                {29,67,98,99},
                {100,245,900,950}
        });

        assertTrue(interview.contains(1));
        assertTrue(interview.contains(67));
        assertTrue(interview.contains(950));

        assertFalse(interview.contains(35));
    }

    @Test
    void anyShape() {
        Interview<Integer> interview = new Interview<>(new Integer[][] {
                {1, 2, 5, 18, 20},
                {29, 67, 98, 100, 245, 900, 949},
                {950, 1000, 1020},
                {1035}
        });

        assertTrue(interview.contains(5));
        assertTrue(interview.contains(245));
        assertTrue(interview.contains(1000));
        assertTrue(interview.contains(1035));

        assertFalse(interview.contains(3));
    }

    @Test
    void bounds() {
        Interview<Integer> interview = new Interview<>(new Integer[][] {
                {1,2,5},
                {29,67,98},
                {101,245,900}
        });

        assertFalse(interview.contains(0));
        assertTrue(interview.contains(1));
        assertTrue(interview.contains(5));
        assertFalse(interview.contains(6));

        assertFalse(interview.contains(28));
        assertTrue(interview.contains(29));
        assertTrue(interview.contains(98));
        assertFalse(interview.contains(99));

        assertFalse(interview.contains(100));
        assertTrue(interview.contains(101));
        assertTrue(interview.contains(900));
        assertFalse(interview.contains(901));
    }
}
