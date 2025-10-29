#include <queue>
#include <vector>
#include <functional>

/**
 * MedianFinder 类：用于在数据流中高效地查找中位数
 * 核心思想：使用两个优先队列来维护数据的上下两半部分
 * - queMin（大顶堆）：存储较小的那一半数据，堆顶是较小部分的最大值
 * - queMax（小顶堆）：存储较大的那一半数据，堆顶是较大部分的最小值
 * 通过维护两个堆的大小关系，保证：
 * 1. queMin.size() >= queMax.size()
 * 2. queMin.size() - queMax.size() <= 1
 * 这样中位数要么是queMin的堆顶，要么是两个堆顶的平均值
 */
class MedianFinder {
public:
    priority_queue<int, vector<int>, less<int>> queMin;
    priority_queue<int, vector<int>, greater<int>> queMax;

    /**
     * 构造函数：初始化两个空优先队列
     */
    MedianFinder() {}

    /**
     * 添加一个数字到数据流中，并维护两个堆的平衡
     * @param num 要添加的整数
     */
    void addNum(int num) {
        // 策略：如果num小于等于queMin的堆顶，或者queMin为空，将其加入queMin
        // 否则，将其加入queMax
        if (queMin.empty() || num <= queMin.top()) {
            queMin.push(num);
            // 维护堆的平衡：如果queMin比queMax大超过1个元素，则将queMin的堆顶移到queMax
            if (queMax.size() + 1 < queMin.size()) {
                queMax.push(queMin.top());
                queMin.pop();
            }
        } else {
            queMax.push(num);
            // 维护堆的平衡：如果queMax的大小超过queMin，则将queMax的堆顶移到queMin
            if (queMax.size() > queMin.size()) {
                queMin.push(queMax.top());
                queMax.pop();
            }
        }
    }

    /**
     * 查找当前数据流中的中位数
     * @return 当前数据流的中位数
     */
    double findMedian() {
        // 如果queMin比queMax多一个元素，中位数就是queMin的堆顶
        if (queMin.size() > queMax.size()) {
            return queMin.top();
        }
        // 否则，中位数是两个堆顶的平均值
        return (queMin.top() + queMax.top()) / 2.0;
    }
};

/**
 * 时间复杂度分析：
 * - addNum 方法：O(log n)，其中n是已添加元素的数量。优先队列的插入和删除操作均为O(log n)
 * - findMedian 方法：O(1)，直接返回堆顶元素
 * 
 * 空间复杂度：O(n)，需要存储所有已添加的元素
 */
