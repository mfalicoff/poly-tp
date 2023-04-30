# Matricules
# Maximiliano Falicoff 2013658
# Julien Savoldelli 2229682

# search.py
# ---------
# Licensing Information:  You are free to use or extend these projects for
# educational purposes provided that (1) you do not distribute or publish
# solutions, (2) you retain this notice, and (3) you provide clear
# attribution to UC Berkeley, including a link to http://ai.berkeley.edu.
#
# Attribution Information: The Pacman AI projects were developed at UC Berkeley.
# The core projects and autograders were primarily created by John DeNero
# (denero@cs.berkeley.edu) and Dan Klein (klein@cs.berkeley.edu).
# Student side autograding was added by Brad Miller, Nick Hay, and
# Pieter Abbeel (pabbeel@cs.berkeley.edu).


"""
In search.py, you will implement generic search algorithms which are called by
Pacman agents (in searchAgents.py).
"""

import util


class SearchProblem:
    """
    This class outlines the structure of a search problem, but doesn't implement
    any of the methods (in object-oriented terminology: an abstract class).

    You do not need to change anything in this class, ever.
    """

    def getStartState(self):
        """
        Returns the start state for the search problem.
        """
        util.raiseNotDefined()

    def isGoalState(self, state):
        """
          state: Search state

        Returns True if and only if the state is a valid goal state.
        """
        util.raiseNotDefined()

    def getSuccessors(self, state):
        """
          state: Search state

        For a given state, this should return a list of triples, (successor,
        action, stepCost), where 'successor' is a successor to the current
        state, 'action' is the action required to get there, and 'stepCost' is
        the incremental cost of expanding to that successor.
        """
        util.raiseNotDefined()

    def getCostOfActions(self, actions):
        """
         actions: A list of actions to take

        This method returns the total cost of a particular sequence of actions.
        The sequence must be composed of legal moves.
        """
        util.raiseNotDefined()


def tinyMazeSearch(problem):
    """
    Returns a sequence of moves that solves tinyMaze.  For any other maze, the
    sequence of moves will be incorrect, so only use this for tinyMaze.
    """
    from game import Directions

    s = Directions.SOUTH
    w = Directions.WEST
    return [s, s, w, s, w, w, s, w]


def test(node, parent):
    action = node[1]
    if action is None: return []
    return test(parent[node], parent) + [action]


def searchWhithoutCost(problem, queue):
    start_node = (problem.getStartState(), [], 0)
    queue.push(start_node)
    visited = []

    while not queue.isEmpty():
        (current_coords, direction, cost) = queue.pop()

        if current_coords not in visited:
            visited.append(current_coords)

            if problem.isGoalState(current_coords):
                return direction

            children = problem.getSuccessors(current_coords)

            for (child_coords, child_dir, child_cost) in children:
                if child_coords not in visited:
                    queue.push((child_coords, direction + [child_dir], child_cost))

def depthFirstSearch(problem):
    return searchWhithoutCost(problem, util.Stack())


def breadthFirstSearch(problem):
    """Search the shallowest nodes in the search tree first."""

    return searchWhithoutCost(problem, util.Queue())


def uniformCostSearch(problem):
    """Search the node of least total cost first."""

    """
        INSÉREZ VOTRE SOLUTION À LA QUESTION 3 ICI
    """
    queue = util.PriorityQueue()
    start_node = (problem.getStartState(), [], 0)
    queue.push(start_node, start_node[2])
    visited = []

    while not queue.isEmpty():
        curr = queue.pop()
        if not curr[0] in visited:
            visited.append(curr[0])
            if problem.isGoalState(curr[0]):
                return curr[1]
            succ = problem.getSuccessors(curr[0])
            for x in succ:
                if not x[0] in visited:
                    queue.push((x[0], curr[1] + [x[1]], curr[2] + x[2]), curr[2] + x[2])


def nullHeuristic(state, problem=None):
    """
    A heuristic function estimates the cost from the current state to the nearest
    goal in the provided SearchProblem.  This heuristic is trivial.
    """
    return 0


def aStarSearch(problem, heuristic=nullHeuristic):
    """Search the node that has the lowest combined cost and heuristic first."""
    """
        INSÉREZ VOTRE SOLUTION À LA QUESTION 4 ICI
    """
    queue = util.PriorityQueue()
    start_node = (problem.getStartState(), [], 0)
    queue.push(start_node, heuristic(start_node[0], problem))
    visited = []

    while not queue.isEmpty():
        curr = queue.pop()
        if not curr[0] in visited:
            visited.append(curr[0])
            if problem.isGoalState(curr[0]):
                return curr[1]
            succ = problem.getSuccessors(curr[0])
            for x in succ:
                if not x[0] in visited:
                    queue.push((x[0], curr[1] + [x[1]], curr[2] + x[2]), curr[2] + x[2] + heuristic(x[0], problem))


# Abbreviations
bfs = breadthFirstSearch
dfs = depthFirstSearch
astar = aStarSearch
ucs = uniformCostSearch
