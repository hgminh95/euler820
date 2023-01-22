# euler820

Code examples for this blog post: https://hgminh.dev/posts/solving-project-euler-820-on-different-hardwares-part-1/

To run one example, try below command

```bash
$ bazel run --config m2 --run_under "time " --copt -DM_N=100000000 :multi_thread_with_unroll
```

To run the whole benchmark,

```bash
$ ./benchmark.sh <arch>

$ ./benchmark.sh m2
...
```
