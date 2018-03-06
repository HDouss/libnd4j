// <auto-generated>
//  automatically generated by the FlatBuffers compiler, do not modify
// </auto-generated>

namespace nd4j.graph
{

using global::System;
using global::FlatBuffers;

public struct FlatResult : IFlatbufferObject
{
  private Table __p;
  public ByteBuffer ByteBuffer { get { return __p.bb; } }
  public static FlatResult GetRootAsFlatResult(ByteBuffer _bb) { return GetRootAsFlatResult(_bb, new FlatResult()); }
  public static FlatResult GetRootAsFlatResult(ByteBuffer _bb, FlatResult obj) { return (obj.__assign(_bb.GetInt(_bb.Position) + _bb.Position, _bb)); }
  public void __init(int _i, ByteBuffer _bb) { __p.bb_pos = _i; __p.bb = _bb; }
  public FlatResult __assign(int _i, ByteBuffer _bb) { __init(_i, _bb); return this; }

  public long Id { get { int o = __p.__offset(4); return o != 0 ? __p.bb.GetLong(o + __p.bb_pos) : (long)0; } }
  public FlatVariable? Variables(int j) { int o = __p.__offset(6); return o != 0 ? (FlatVariable?)(new FlatVariable()).__assign(__p.__indirect(__p.__vector(o) + j * 4), __p.bb) : null; }
  public int VariablesLength { get { int o = __p.__offset(6); return o != 0 ? __p.__vector_len(o) : 0; } }
  public FlatTiming? Timing(int j) { int o = __p.__offset(8); return o != 0 ? (FlatTiming?)(new FlatTiming()).__assign(__p.__indirect(__p.__vector(o) + j * 4), __p.bb) : null; }
  public int TimingLength { get { int o = __p.__offset(8); return o != 0 ? __p.__vector_len(o) : 0; } }
  public long FootprintForward { get { int o = __p.__offset(10); return o != 0 ? __p.bb.GetLong(o + __p.bb_pos) : (long)0; } }
  public long FootprintBackward { get { int o = __p.__offset(12); return o != 0 ? __p.bb.GetLong(o + __p.bb_pos) : (long)0; } }

  public static Offset<FlatResult> CreateFlatResult(FlatBufferBuilder builder,
      long id = 0,
      VectorOffset variablesOffset = default(VectorOffset),
      VectorOffset timingOffset = default(VectorOffset),
      long footprintForward = 0,
      long footprintBackward = 0) {
    builder.StartObject(5);
    FlatResult.AddFootprintBackward(builder, footprintBackward);
    FlatResult.AddFootprintForward(builder, footprintForward);
    FlatResult.AddId(builder, id);
    FlatResult.AddTiming(builder, timingOffset);
    FlatResult.AddVariables(builder, variablesOffset);
    return FlatResult.EndFlatResult(builder);
  }

  public static void StartFlatResult(FlatBufferBuilder builder) { builder.StartObject(5); }
  public static void AddId(FlatBufferBuilder builder, long id) { builder.AddLong(0, id, 0); }
  public static void AddVariables(FlatBufferBuilder builder, VectorOffset variablesOffset) { builder.AddOffset(1, variablesOffset.Value, 0); }
  public static VectorOffset CreateVariablesVector(FlatBufferBuilder builder, Offset<FlatVariable>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartVariablesVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static void AddTiming(FlatBufferBuilder builder, VectorOffset timingOffset) { builder.AddOffset(2, timingOffset.Value, 0); }
  public static VectorOffset CreateTimingVector(FlatBufferBuilder builder, Offset<FlatTiming>[] data) { builder.StartVector(4, data.Length, 4); for (int i = data.Length - 1; i >= 0; i--) builder.AddOffset(data[i].Value); return builder.EndVector(); }
  public static void StartTimingVector(FlatBufferBuilder builder, int numElems) { builder.StartVector(4, numElems, 4); }
  public static void AddFootprintForward(FlatBufferBuilder builder, long footprintForward) { builder.AddLong(3, footprintForward, 0); }
  public static void AddFootprintBackward(FlatBufferBuilder builder, long footprintBackward) { builder.AddLong(4, footprintBackward, 0); }
  public static Offset<FlatResult> EndFlatResult(FlatBufferBuilder builder) {
    int o = builder.EndObject();
    return new Offset<FlatResult>(o);
  }
  public static void FinishFlatResultBuffer(FlatBufferBuilder builder, Offset<FlatResult> offset) { builder.Finish(offset.Value); }
};


}
